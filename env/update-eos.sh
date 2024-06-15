#!/bin/bash
WD=`pwd`

for arg in $@; do
	case "$arg" in
    	-h)
	   		echo "$0 [ EOS_HOME0 [ EOS_GITUSER0 ] ]";
	     	echo "    EOS_HOME0    : directory name to be installed.";
		  	echo "    EOS_GITUSER0 : OSDN account.";
		   	exit 1;
		  	;;
		-*) echo "unsupported option $arg"; exit 1;;
	esac
done

case $# in
	0)
		;;
	1)
		EOS_HOME0=$1
		;;
	2)
		EOS_HOME0=$1
		EOS_GITUSER0=$2
		;;
	*)
esac

if [ -z $EOS_HOME0 ] ; then
	echo "Please set an environment for Eos."
	echo " $ export EOS_HOME0=InstalledDirOfEos"
	echo "      or   "
	echo -n "Set EOS_HOME0 [$EOS_HOME] :" 
	read EOS_HOME0
	if [ -z $EOS_HOME0 ] ; then
		export EOS_HOME0=$EOS_HOME
	fi 
fi

if [ -z $EOS_GITUSER0 ] ; then
	echo -n "If you want to set a gitacount on OSDN, Set EOS_GITUSER0 or just return. : "
	read EOS_GITUSER0
fi

echo "EOS_HOME0:    $EOS_HOME0"
if [ -z $EOS_GITUSER0 ] ; then
	echo "EOS_GITUSER0: NoGitAccount"
else
	echo "EOS_GITUSER0: $EOS_GITUSER0"
fi	

unset ANS
echo -n "Is is OK ? [ Y|y or N|n ] : "
read ANS

case $ANS in
	Y|y)
		;;	
	*)
		echo " $ export EOS_HOME0=InstalledDirOfEos"
		echo " $ export EOS_GITUSER0=GitUserForOSDN"
		echo "      or "
		echo " $ export EOS_GITUSER0="
		echo " $ source update-eos.sh"; exit 1
		;;
esac

unset FLAG_BASHPROFILE 
echo -n "Do you want to modify .bash_profile automatically ? [ Y|y or N|n ] : "; read FLAG_BASHPROFILE 
unset FLAG_BASHRC
echo -n "Do you want to modify .bashrc automatically ? [ Y|y or N|n ] : "; read FLAG_BASHRC

#
# Start updating
#

EOS_HOME=$EOS_HOME0
EOS_GITUSER=$EOS_GITUSER0

ROOT_EOS_OSDN_GIT=git://git.osdn.jp/gitroot/eos/base.git
ROOT_EOS_OSDN_HTTP=http://scm.osdn.jp/gitroot/eos/base.git
ROOT_EOS_OSDN_SSH=${EOS_GITUSER}@git.osdn.jp:/gitroot/eos/base.git
ROOT_EOS_OSDN_HTTPS=https://scm.osdn.jp/gitroot/eos/base.git

if [ ! -d $EOS_HOME/.git ] ; then
	echo "Not installed"
	echo "Use install-eos.sh for updating or make concern env of EOS_HOME or EOS_HOME0. Current vars are $EOS_HOME and $EOS_HOME0."
else
	if [ -z $EOS_GITUSER ] ; then
		cd $EOS_HOME; echo "No EOS_GITUSER."; 
		git pull $ROOT_EOS_OSDN_GIT  || \
		git pull $ROOT_EOS_OSDN_HTTP || \
		echo "A port for git (9418) or HTTP is not open, or something wrong."
		INSTALL_FLAG=
	else
		cd $EOS_HOME; echo "$EOS_GITUSER as EOS_GITUSER";  
		git pull $ROOT_EOS_OSDN_SSH || \
		git pull --depth 1 $ROOT_EOS_OSDN_HTTPS || \
			echo "A port for SSH or HTTPS is not open, or something wrong for $EOS_GITUSER."
		INSTALL_FLAG=INSTALL
	fi
fi


test -r $EOS_HOME/env/Eos_env  && source $EOS_HOME/env/Eos_env || echo "Not found $EOS_HOME/env/Eos_env"

if [ -z ${EOS_HOSTDIR} ] ; then
	echo "Set EOS_HOSTDIR. Current is $EOS_HOSTDIR"; exit;
else
	echo "hostdepend for ${EOS_HOSTDIR}"
fi

HOSTDEPEND_EOS_OSDN_GIT=git://git.osdn.jp/gitroot/eos/hostdepend${EOS_HOSTDIR}.git
HOSTDEPEND_EOS_OSDN_HTTP=http://scm.osdn.jp/gitroot/eos/hostdepend${EOS_HOSTDIR}.git
HOSTDEPEND_EOS_OSDN_SSH=${EOS_GITUSER}@git.osdn.jp:/gitroot/eos/hostdepend${EOS_HOSTDIR}.git
HOSTDEPEND_EOS_OSDN_HTTPS=https://scm.osdn.jp/gitroot/eos/hostdepend${EOS_HOSTDIR}.git

if [ -d $EOS_HOME/hostdepend ] ; then
    cd $EOS_HOME/hostdepend/ 
    if [ ! -d ${EOS_HOSTDIR}/.git ] ; then
        echo "Not installed hostdepend/${EOS_HOSTDIR}"; 
        echo "Use install-eos.sh for updating or set a new directory for update"
    else 
		cd ${EOS_HOSTDIR}
        if [ -z $EOS_GITUSER ] ; then
            git pull ${HOSTDEPEND_EOS_OSDN_GIT}  || \
            git pull ${HOSTDEPEND_EOS_OSDN_HTTP} || \
            echo "A port for git (9418) or HTTP is not open, or something wrong."
            INSTALL_FLAG=
        else 
            git pull ${HOSTDEPEND_EOS_OSDN_SSH}   || \
            git pull ${HOSTDEPEND_EOS_OSDN_HTTPS} || \
            echo "A port for SSH or HTTPS is not open, or something wrong."
            INSTALL_FLAG=INSTALL
        fi  
    fi  
else
    echo "No hostdepend dir"
fi

cd $WD

#
# automatic profile update
#
case $FLAG_BASHPROFILE in 
	Y|y) 
		awk 'BEGIN {EOS="no"} {if($0=="## Eos_env Start") EOS="yes"; if(EOS!="yes") print $0;if($0=="## Eos_env End") EOS="no"; }' $HOME/.bash_profile > $HOME/.bash_profile.org
		cat $HOME/.bash_profile.org > $HOME/.bash_profile
		if [ -f $EOS_HOME/env/template.bashrc ] ; then
			cat $EOS_HOME/env/template.bashrc >> $HOME/.bash_profile
		else
			cat >> $HOME/.bash_profile << EOF 

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
EOF
		fi
		;;
	*)
		echo "Please set your preferable environment as you like."
		echo "Or"
		echo "$ source $EOS_HOME/env/Eos_env"
		;;
esac


#
#

case $FLAG_BASHRC in 
	Y|y) 
		awk 'BEGIN {EOS="no"} {if($0=="## Eos_env Start") EOS="yes"; if(EOS!="yes") print $0;if($0=="## Eos_env End") EOS="no"; }' $HOME/.bashrc > $HOME/.bashrc.org
		cat $HOME/.bashrc.org > $HOME/.bashrc
		if [ -f $EOS_HOME/env/template.bashrc ] ; then
			cat $EOS_HOME/env/template.bashrc >> $HOME/.bashrc
		else
			cat >> $HOME/.bashrc << EOF 
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
EOF
		fi	
		;;
	*)
		echo "Please set your preferable environment as you like."
		echo "Or"
		echo "$ source $EOS_HOME/env/Eos_env"
		;;
esac


cd $WD
