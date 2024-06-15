## Eos_env Start
##

if [ ! -z $EOS_HOME0 ] ; then 
    if [ -f $EOS_HOME0/env/Eos_env -a ! -f $HOME/.Eos_env ] ; then
        ln -s $EOS_HOME0/env/Eos_env $HOME/.Eos_env
    fi  
fi

export EOS_HOME0=$EOS_HOME0
export EOS_GITUSER0=$EOS_GITUSER0

test -r $HOME/.Eos_env  && . $HOME/.Eos_env

##
## Eos_env End 
