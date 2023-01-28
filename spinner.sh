#!/bin/bash
DEFAULT_SpinnerFrames=("—" "\\" "|" "/")

# Credit for the lovely spinner sequences
# https://unix.stackexchange.com/a/565551/248440

Spinner_Dot=("⠁" "⠂" "⠄" "⡀" "⢀" "⠠" "⠐" "⠈")
Spinner_Vertical=("▁" "▂" "▃" "▄" "▅" "▆" "▇" "█" "▇" "▆" "▅" "▄" "▃" "▂" "▁")
Spinner_Horizontal=("▉" "▊" "▋" "▌" "▍" "▎" "▏" "▎" "▍" "▌" "▋" "▊" "▉")
Spinner_Arrows=("←" "↖" "↑" "↗" "→" "↘" "↓" "↙")
Spinner_WHAT=("▖" "▘" "▝" "▗")
Spinner_WHAT2=("┤" "┘" "┴" "└" "├" "┌" "┬" "┐")
Spinner_Triangle=("◢" "◣" "◤" "◥")
Spinner_Square=("◰" "◳" "◲" "◱")
Spinner_Quarters=("◴" "◷" "◶" "◵")
Spinner_Halves=("◐" "◓" "◑" "◒")
Spinner_Braille=("⣾" "⣽" "⣻" "⢿" "⡿" "⣟" "⣯" "⣷")

## @function: spinner(action, label, &spinnerFramesRef[])
##
## @description: Perform an action asynchronously and display
## spinner till action is completed
##
## @param action: The action the execute
## @param label: The label to display while waiting
## @param spinnerRef: In case you feel like a custom spinner, pass a ref to an array of strings
spinner() {
  local frameRef
  local action="${1}"
  local label="${2} "
  local spinnerRef="${3-DEFAULT_SpinnerFrames}"
  local spinnerFrames=$(eval "echo \${!${spinnerRef}[@]}")
   # echo ${action} ${label}
  spinnerRun() {
    while true; do
      for frame in ${spinnerFrames[@]}; do
        frameRef="${spinnerRef}[${frame}]"
        echo "${label}${!frameRef}"
        tput cuu1 tput el
        sleep 0.2
      done
    done
    echo -e "\r"
  }

  spinnerRun &
  local spinnerPid=$!
  ${action}
  kill "${spinnerPid}"
}
spinner "${1}" "${2}" "${3}"
