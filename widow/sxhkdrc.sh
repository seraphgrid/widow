#!/bin/bash

# Define the paths to your configuration files
VIM_MODE="$HOME/.config/sxhkd/sxhkdrc"          # Main configuration file
INSERT_MODE="$HOME/.config/sxhkd/sxhkdrc_ins"  # Keyboard-respecting configuration file
MODE_FILE="$HOME/.config/sxhkd/current_mode"      # File to store the current mode

# Function to restart sxhkd with a specified configuration
restart_sxhkd() {
    local config_file="$1"
    
    # Kill any running instance of sxhkd
    killall sxhkd

    sleep 0.1
    
    # Start sxhkd with the specified configuration file
    sxhkd -c "$config_file" &

}

# Function to toggle between modes
toggle_mode() {

    if [[ -f "$MODE_FILE" ]]; then
        current_mode=$(cat "$MODE_FILE")
    else
        current_mode="VIM"  # Default to insert mode if no file exists
    fi

    if [[ "$current_mode" == "INS" ]]; then
        restart_sxhkd "$VIM_MODE"         
        echo "VIM" > "$MODE_FILE"
       
    else
        restart_sxhkd "$INSERT_MODE"
        killall warpd
        echo "INS" > "$MODE_FILE"
        
    fi
}

# Function to show the current mode
show_current_mode() {
    if [[ -f "$MODE_FILE" ]]; then
        current_mode=$(cat "$MODE_FILE")
    else
        current_mode="VIM"  # Default to emacs mode if no file exists
    fi
    notify-send "MODE: $current_mode"
}

# Check for flags
case "$1" in
    -v)
        restart_sxhkd "$VIM_MODE"
        echo "VIM" > "$MODE_FILE"
        # Start warpd only if it's not already running
        if ! pgrep -x "warpd" > /dev/null; then
            exec warpd -c "~/.config/warpd/config" & 
        fi
        ;;
    -i)
        restart_sxhkd "$INSERT_MODE"
        echo "INS" > "$MODE_FILE"
        killall warpd 2>/dev/null
        ;;
    -t)
        toggle_mode
        ;;
    -s)
        show_current_mode
        ;;
    *)
        echo "Usage: $0 -v | -i | -t | -s"
        echo "  -v: VIM MODE ENABLE"
        echo "  -i: INSERT MODE ENABLE"
        echo "  -t: TOGGLE BETWEEN EMACS AND INSERT MODE"
        echo "  -s: SHOW CURRENT MODE"
        ;;
esac
