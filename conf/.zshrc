# Path to your oh-my-zsh installation.
export ZSH="$HOME/.oh-my-zsh"

# See https://github.com/robbyrussell/oh-my-zsh/wiki/Themes
ZSH_THEME="robbyrussell_edit"

# Which plugins would you like to load?
plugins=(git colored-man-pages colorize command-not-found copyfile 
         compleat extract
         zsh-syntax-highlighting
         command-time
         fzf-tab)

source $ZSH/oh-my-zsh.sh

# dont't put commands starting with space in zsh history
setopt HIST_IGNORE_SPACE

ZSH_COMMAND_TIME_COLOR="cyan"
LS_COLORS+=':ow=01;33'
export FZF_DEFAULT_OPTS='--height 100%'
source /usr/share/doc/fzf/examples/key-bindings.zsh
source /usr/share/doc/fzf/examples/completion.zsh

# disable sort when completing `git checkout`
zstyle ':completion:*:git-checkout:*' sort false
# set descriptions format to enable group support
zstyle ':completion:*:descriptions' format '[%d]'
# set list-colors to enable filename colorizing
zstyle ':completion:*' list-colors ${(s.:.)LS_COLORS}
# preview directory's content with exa when completing cd
zstyle ':fzf-tab:complete:cd:*' fzf-preview 'exa -1 --color=always $realpath'
# # switch group using `,` and `.`
zstyle ':fzf-tab:*' switch-group ',' '.'

alias vim="nvim"
alias oldvim="\vim"
[ -f "/home/rahul/.ghcup/env" ] && source "/home/rahul/.ghcup/env" # ghcup-env
export PATH="$PATH:$HOME/.cabal/bin"
export PATH="$PATH:$HOME/.local/bin"

export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion

# C++ compile and run.
function rr() {
  g++ -DRahul -O2 --std=c++23 "$1" && ./a.out
}
NVIM_APPNAME=lazyvim


#THIS MUST BE AT THE END OF THE FILE FOR SDKMAN TO WORK!!!
export SDKMAN_DIR="$HOME/.sdkman"
[[ -s "$HOME/.sdkman/bin/sdkman-init.sh" ]] && source "$HOME/.sdkman/bin/sdkman-init.sh"
