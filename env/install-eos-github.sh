#RCRC!/bin/bash
#### 
WD=`pwd`

for arg in $@; do
	case "$arg" in 
		-h) 
			echo "$0 [ EOS_HOME0 [ EOS_GITUSER0 ] ]"; 
			echo "    EOS_HOME0    : directory name to be installed."; 
			echo "    EOS_GITUSER0 : GITHUB account."; 
			exit 1;
			;;
		-*) echo "unsupported option $arg"; exit 1;;
	esac
done

case $# in 
	0)
		if [ -z $EOS_HOME0 ] ; then
			EOS_HOME0=$HOME/Eos
		fi
		if [ -z $EOS_GITUSER0 ] ; then
			EOS_GITUSER0=$USER
		fi
		;;
	1)
		export EOS_HOME0=$1
		if [ -z $EOS_GITUSER0 ] ; then
			EOS_GITUSER0=$USER
		fi
		;;
	2)
		export EOS_HOME0=$1
		export EOS_GITUSER0=$2
		;;
esac		

function setEosHome0() {
	#
	# EOS_HOME0
	#
	echo -n "Set the directroy to be installed [$EOS_HOME0]: "; read ANS
	if [ ! -z $ANS ] ; then 
		EOS_HOME0=$ANS;
	fi
	unset ANS
	echo "Directory: $EOS_HOME0";
	return 1
}

function setEosGitUser0() {
	#
	# EOS_GITUSER0
	#
	echo -n "Do you have your git account for GITHUB [Y|y or N|n] ?"; read ANS
	case $ANS in 
		N|n) 
			export EOS_GITUSER0=
			;;
		Y|y)
			unset ANS
			echo -n "Set the git account for GITHUB [$EOS_GITUSER0]: "; read ANS 
			if [ ! -z $ANS ] ; then
				export EOS_GITUSER0=$ANS
			fi
			;;
		*)	
			echo "Please run install-eos.sh again!"
			exit 1
			;;
	esac
	return 1
}

function surelyHome0andGitUser0() {
	echo "Directory:   $EOS_HOME0"
	if [ -z $EOS_GITUSER0 ] ; then
		echo "GIT Account: NoAcount"
	else 
		echo "GIT Account: $EOS_GITUSER0"
	fi
	unset ANS
	echo -n "Are these parameters OK [Y|y or N|n]? "; read ANS

	case $ANS in
		Y|y) 
			echo "Directory:   $EOS_HOME0"
			echo "GIT Account: $EOS_GITUSER0"
			;;
		*)
			echo "Please run $0 again!"
			exit
			;;
	esac
	return 1 
}

case $# in
	0)
		setEosHome0
		setEosGitUser0
		;;
	1)	
		setEosGitUser0
		;;
	2)
		;;
	*)
		echo "Please run $0 again!"
		exit
		;;
esac

unset FLAG_BASHPROFILE 
echo -n "Do you want to rewrite $HOME/.bash_prfile ? [Y|y or N|n] " ; read FLAG_BASHPROFILE 
unset FLAG_BASHRC
echo -n "Do you want to rewrite $HOME/.bashrc ? [Y|y or N|n] " ; read FLAG_BASHRC
unset FLAG_ZSHRC
echo -n "Do you want to rewrite $HOME/.zshrc ? [Y|y or N|n] " ; read FLAG_ZSHRC
unset FLAG_ZPROFILE
echo -n "Do you want to rewrite $HOME/.zprofile ? [Y|y or N|n] " ; read FLAG_ZPROFILE 


#### No Change
#ROOT_EOS_SOURCEFORGE=https://sourceforge.jp/projects/eos/scm/git/base/blobs/master/
ROOT_EOS_GITHUB_GIT=git://git.osdn.jp/gitroot/eos/base.git
ROOT_EOS_GITHUB_HTTP=http://scm.osdn.jp/gitroot/eos/base.git
ROOT_EOS_GITHUB_SSH=${EOS_GITUSER0}@git.osdn.jp:/gitroot/eos/base.git
ROOT_EOS_GITHUB_HTTPS=https://scm.osdn.jp/gitroot/eos/base.git


if [ ! -d $EOS_HOME0 ] ; then
	mkdir $EOS_HOME0
fi

#curl -L $ROOT_EOS_SOURCEFORGE/env/Eos_env?export=raw | sh - ; 

if [ -d $EOS_HOME0/.git ] ; then
	echo "Already installed"
	echo "Use update-eos.sh for updating or set a new directory for installation"
	exit 1
else
	if [ -z $EOS_GITUSER0 ] ; then
		INSTALL_FLAG=
	else 
		git clone --depth 1 $ROOT_EOS_GITHUB_SSH $EOS_HOME0 || \
		git clone --depth 1 $ROOT_EOS_GITHUB_HTTPS $EOS_HOME0 || \
		echo "A port for SSH or HTTPS is not open, or something wrong for $EOS_GITUSER0."
		INSTALL_FLAG="GITUSER"
	fi
	if [ -z $INSTALL_FLAG ] ; then
		git clone --depth 1 $ROOT_EOS_GITHUB_GIT  $EOS_HOME0 || \
		git clone --depth 1 $ROOT_EOS_GITHUB_HTTP $EOS_HOME0 || \
		echo "A port for git (9418) or HTTP is not open, or something wrong."
		INSTALL_FLAG="NOGITUSER"
	fi
fi

#
# hostdepend
#

if [ ! -f $HOME/.Eos_env ] ; then
	echo "No .Eos_env"
	ln -sf $EOS_HOME0/env/Eos_env $HOME/.Eos_env 
fi

test -r $HOME/.Eos_env || . $HOME/.Eos_env || "Prepare environment"
echo "hostdepend for ${EOS_HOSTDIR}"
case $INSTALL_FLAG in
	NOGITUSER)
		export EOS_GITUSER0=
		;;
esac

HOSTDEPEND_EOS_GITHUB_GIT=git://git.osdn.jp/gitroot/eos/hostdepend${EOS_HOSTDIR}.git
HOSTDEPEND_EOS_GITHUB_HTTP=http://scm.osdn.jp/gitroot/eos/hostdepend${EOS_HOSTDIR}.git
HOSTDEPEND_EOS_GITHUB_SSH=${EOS_GITUSER0}@git.osdn.jp:/gitroot/eos/hostdepend${EOS_HOSTDIR}.git
HOSTDEPEND_EOS_GITHUB_HTTPS=https://scm.osdn.jp/gitroot/eos/hostdepend${EOS_HOSTDIR}.git

if [ ! -d $EOS_HOME0/hostdepend ] ; then
	mkdir $EOS_HOME0/hostdepend	
fi	

if [ -d $EOS_HOME0/hostdepend ] ; then
	cd $EOS_HOME0/hostdepend/;  
	if [ -d ${EOS_HOSTDIR}/.git ] ; then
		echo "Already installed hostdepend/${EOS_HOSTDIR}"; 
		echo "Use update-eos.sh for updating or set a new directory for installation"
	else 
		if [ -z $EOS_GITUSER0 ] ; then
			INSTALL_FLAG=
		else 
			git clone --depth 1 ${HOSTDEPEND_EOS_GITHUB_SSH} ${EOS_HOSTDIR} || \
			git clone --depth 1 ${HOSTDEPEND_EOS_GITHUB_HTTPS} ${EOS_HOSTDIR} || \
			echo "A port for SSH or HTTPS is not open, or something wrong."
 			cd ${EOS_HOSTDIR}; \
 			git clone --unshallow ${HOSTDEPEND_EOS_GITHUB_SSH} || \
 			git clone --unshallow 1 ${HOSTDEPEND_EOS_GITHUB_HTTPS} || \
 			echo "cannot --unshallow something wrong."
			INSTALL_FLAG=INSTALL
		fi
		if [ -z $INSTALL_FLAG ] ; then
			git clone --depth 1 ${HOSTDEPEND_EOS_GITHUB_GIT} ${EOS_HOSTDIR} || \
			git clone --depth 1 ${HOSTDEPEND_EOS_GITHUB_HTTP} ${EOS_HOSTDIR} || \
			echo "A port for git (9418) or HTTP is not open, or something wrong."
		fi
	fi
else
	echo "Cannot make hostdepend"
fi


#
# .bash_profile or .zshprofile
#
echo "Setting an environment for Eos"

case $FLAG_BASHPROFILE in 
	Y|y)
		awk 'BEGIN {EOS="no"} {if($0=="## Eos_env Start") EOS="yes"; if(EOS!="yes") print $0;if($0=="## Eos_env End") EOS="no"; }' $HOME/.bash_profile > $HOME/.bash_profile.org

		cat $HOME/.bash_profile.org > $HOME/.bash_profile
		if [ -f $EOS_HOME/env/template.bashrc ] ; then
			cat $EOS_HOME/env/template.bashrc >>  $HOME/.bash_profile
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
		echo "Please check $HOME/.bash_profile."
		;;

	*)
		echo "Before you use Eos, "
		echo 'source $EOS_HOME0/env/Eos_env'
		echo "  or " 
		echo "You should rewrite $HOME/.bash_profile by yourself to execute $EOS_HOME0/env/Eos_env."
		;;
esac

case $FLAG_ZSHPROFILE in 
	Y|y)
		awk 'BEGIN {EOS="no"} {if($0=="## Eos_env Start") EOS="yes"; if(EOS!="yes") print $0;if($0=="## Eos_env End") EOS="no"; }' $HOME/.zprofile > $HOME/.zprofile.org

		cat $HOME/.zprofile.org > $HOME/.zprofile
		if [ -f $EOS_HOME/env/template.zshrc ] ; then
			cat $EOS_HOME/env/template.zshrc >>  $HOME/.zprofile
		else 
			cat >> $HOME/.zprofile << EOF
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
		echo "Please check $HOME/.zprofile."
		;;

	*)
		echo "Before you use Eos, "
		echo 'source $EOS_HOME0/env/Eos_env'
		echo "  or " 
		echo "You should rewrite $HOME/.zprofile by yourself to execute $EOS_HOME0/env/Eos_env."
		;;
esac

#
# .bashrc
#

case $FLAG_BASHRC in 
	Y|y)
		awk 'BEGIN {EOS="no"} {if($0=="## Eos_env Start") EOS="yes"; if(EOS!="yes") print $0;if($0=="## Eos_env End") EOS="no"; }' $HOME/.bashrc > $HOME/.bashrc.org

		cat $HOME/.bashrc.org > $HOME/.bashrc
		if [ -f $EOS_HOME/env/template.bashrc ] ; then
			cat  $EOS_HOME/env/template.bashrc >> $HOME/.bashrc
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
		echo "Please check $HOME/.bash_profile."
		;;

	*)
		echo "Before you use Eos, "
		echo 'source $EOS_HOME0/env/Eos_env'
		echo "  or " 
		echo "You should rewrite $HOME/.bash_profile by yourself to execute $EOS_HOME0/env/Eos_env."
		;;
esac


case $FLAG_ZSHRC in 
	Y|y)
		awk 'BEGIN {EOS="no"} {if($0=="## Eos_env Start") EOS="yes"; if(EOS!="yes") print $0;if($0=="## Eos_env End") EOS="no"; }' $HOME/.zshrc > $HOME/.zshrc.org

		cat $HOME/.zshrc.org > $HOME/.zshrc
		if [ -f $EOS_HOME/env/template.zshrc ] ; then
			cat  $EOS_HOME/env/template.zshrc >> $HOME/.zshrc
		else 
			cat >> $HOME/.zshrc << EOF
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
		echo "Please check $HOME/.zshirc"
		;;

	*)
		echo "Before you use Eos, "
		echo 'source $EOS_HOME0/env/Eos_env'
		echo "  or " 
		echo "You should rewrite $HOME/.zshrc by yourself to execute $EOS_HOME0/env/Eos_env."
		;;
esac



#
#
#
echo "You finished Eos installation."

cd $WD
