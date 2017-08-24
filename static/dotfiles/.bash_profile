# /etc/skel/.bash_profile

if [[ -f ~/.bashrc ]] ; then . ~/.bashrc; fi
if [[ -z $DISPLAY ]] && [[ $(tty) = /dev/tty1 ]]; then exec startx; fi
