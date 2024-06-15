SHELL=/bin/bash

EOS_GIT_BACKUPSITE=/net/fs08/fs08/DataBase/EosBackup.git
EOS_GIT_REPOSITRY= git.osdn.jp:/gitroot/eos/base.git 
EOS_GIT_REPOSITRY_NOUSER=git://git.osdn.jp/gitroot/eos/base.git
EOS_GIT_REPOSITRY_OPTIONAL= git.osdn.jp:/gitroot/eos/optional.git 
EOS_GIT_REPOSITRY_OPTIONAL_NOUSER=git://git.osdn.jp/gitroot/eos/optional.git
EOS_GIT_REPOSITRY_TUTORIAL= git.osdn.jp:/gitroot/eos/tutorial.git 
EOS_GIT_REPOSITRY_TUTORIAL_NOUSER=git://git.osdn.jp/gitroot/eos/tutorial.git
EOS_GIT_REPOSITRY_DATA= git.osdn.jp:/gitroot/eos/data.git 
EOS_GIT_REPOSITRY_DATA_NOUSER=git://git.osdn.jp/gitroot/eos/data.git
EOS_GIT_REPOSITRY_OTHERS= git.osdn.jp:/gitroot/eos/others.git 
EOS_GIT_REPOSITRY_OTHERS_NOUSER=git://git.osdn.jp/gitroot/eos/others.git


EOS_GIT_REPOSITRY_HOSTDEPEND=git.osdn.jp:/gitroot/eos/hostdepend
EOS_GIT_REPOSITRY_HOSTDEPEND_NOUSER=git://git.osdn.jp/gitroot/eos/hostdepend

EOS_GIT_REPOSITRY_ZEPHYR= git.osdn.jp:/gitroot/eos/zephyr.git 
EOS_GIT_REPOSITRY_ZEPHYR_NOUSER=git://git.osdn.jp/gitroot/eos/zephyr.git

EOS_GIT_REPOSITRY_PIONE=https://github.com/pione/pione.git
EOS_GIT_REPOSITRY_PIONE_NOUSER=https://github.com/pione/pione.git

help::
	@echo ">> Help"
	@echo ">>>> Download"
	@echo "---- To register new/Modified source codes. ----"
	@echo " $$ make git-add         or git-add[-all|-data|-tutorial|-optional|-others|-others2]" 
	@echo " $$ make git-commit      or git-commit[-all|-data|-tutorial|-optional|-others|-others2]" 
	@echo " $$ make git-tag         or git-tag[-all|-data|-tutorial|-optional|-others|-others2]" 
	@echo " $$ make git-push        or git-push[-all|-data|-tutorial|-optional|-others]" 
	@echo ""
	@echo "---- To fetch and merge new/modified source codes. ----" 
	@echo " $$ make git-fetch       or git-fetch[-all|-data|-tutorial|-optional|-others]" 
	@echo " $$ make git-merge       or git-merge[-all|-data|-tutorial|-optional|-others]" 
	@echo " $$ make setting"
	@echo "---- To init git repository ----"
	@echo " $$ make git-init        or git-init[-all|-zephyr|-data|-tutorial|-optional|-others]" 
	@echo "---- To clonse git repository ----"
	@echo " $$ make git-clone or git-clone[-all|-zephyr|-data|-tutorial|-optional|-others]" 
	@echo "---- option ----"
	@echo "     [] : base only"
	@echo "     [-zephyr]   : zephyr (for GUI/browser)"
	@echo "     [-pione]    : pione  (for process control with GUI/browser)"
	@echo "     [-data]     : data (for test)"
	@echo "     [-tutorial] : tutorial"
	@echo "     [-optional] : optional(for documents)"
	@echo "     [-others] : other source codes for utils"
	@echo "     [-others2] : other source codes for utils"
	@echo "     [-all] : all"
	@echo ""
	@echo ">>>> Setting"
	@echo "---- To set Eos ----"
	@echo " $$ make setting ; # Create links."
	@echo " $$ make install ; # No clean, just install."
	@echo " $$ make rebuild ; # Clean and install."
	@echo " $$ make rebuild-all ; # Update(prototype), clean and install."
	@echo ""
	@echo ">>>> Rebuild"
	@echo "---- To rebuild source codes of Eos ----"
	@echo " $$ make rebuild"
	@echo "---- To update prototype source codes and rebuild source codes of Eos ----"
	@echo " $$ make rebuild-all"
	@echo "---- To set Eos ----"
	@echo " $$ make setting"
	@echo ""
	@echo ">>>> Setting for Eos utils using other softwares "
	@echo "---- To set Eos ----"
	@echo " $$ cd util; make setting"
	@echo " $$ cd util; make rebuild"



rebuild-all: rebuild-src rebuild-Objects rebuild-all-Tools
rebuild: rebuild-src rebuild-Objects rebuild-Tools
install: 
	make install-src 
	make install-Objects 
	make install-Tools

clean:
	cd src/Objects; make clean
	cd src/Tools;   make clean

rebuild-src:
	echo "rebuild-src"
	cd src; rm -f Makefile; cp -f Config/Template/Makefile Makefile 
	cd src; rm -f Objects/Makefile; cp -f Config/Template/ObjectsHomeTemplate.Dir/Makefile Objects/Makefile; \
		rm -f Objects/Config/Target.inc; cp -f Config/Template/ObjectsHomeTemplate.Dir/Config/Target.inc Objects/Config/Target.inc ;  \
		rm -f Objects/Config/Define.inc; sed -e s/worldname/Objects/ Config/Template/ObjectsHomeTemplate.Dir/Config/Define.inc > Objects/Config/Define.inc 
	cd src; rm -f Tools/Makefile; cp -f Config/Template/ToolsHomeTemplate.Dir/Makefile Tools/Makefile; \
		rm -f Tools/Config/Target.inc ; cp -f Config/Template/ToolsHomeTemplate.Dir/Config/Target.inc Tools/Config/Target.inc ; \
		rm -f Tools/Config/Define.inc ; sed  -e s/worldname/Tools/ Config/Template/ToolsHomeTemplate.Dir/Config/Define.inc > Tools/Config/Define.inc 

rebuild-Objects:
	cd src/Objects;  make clean; make check; make depend; make ; make install

rebuild-Tools:
	cd src/Tools;    make clean; make check; make depend; make ; make install

rebuild-all-Tools:
	cd src/Tools;    make clean; make update; make check; make depend; make ; make install

install-src:
	@echo "install-src"
	cd src; rm -f Objects/Makefile; cp -f Config/Template/ObjectsHomeTemplate.Dir/Makefile Objects/Makefile
	cd src; rm -f Tools/Makefile; cp -f Config/Template/ToolsHomeTemplate.Dir/Makefile Tools/Makefile

install-Objects:
	@echo "install-Objects"
	cd src/Objects;  make check; make depend; make ; make install

install-Tools:
	@echo "install-Tools"
	cd src/Tools;    make check; make depend; make ; make install

setting:relink
	if [ ! -d hostdepend ] ; then \
		mkdir hostdepend; \
	fi

relink:
	rm doc; ln -sf optional/doc .
	rm objects;  ln -sf optional/objects .
	rm example; ln -sf data/SampleData example

#
# Add
#

git-add-all:: git-add git-add-data git-add-optional git-add-tutorial git-add-others

git-add:: git-add-hostdepend
	@echo "base directory"
	@git add -v --all . || echo "No files to be added"

git-add-hostdepend::
	@echo "hostdepend directory"
	@cd hostdepend/$${EOS_HOSTDIR}/ ; FLAG=N; \
	for name in `git remote`; do if [ $$name = hostdepend$${EOS_HOSTDIR} ] ; then FLAG=Y; fi; done; \
	if [ $$FLAG = 'N' ] ; then \
	git remote add hostdepend$${EOS_HOSTDIR} $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_HOSTDEPEND)$${EOS_HOSTDIR}.git || echo "Already exist"; \
	fi 
	@cd hostdepend/$${EOS_HOSTDIR}/ ; FLAG=N; \
	for name in `git remote`; do if [ $$name = origin ] ; then FLAG=Y; fi; done; \
	if [ $$FLAG = 'N' ] ; then \
	git remote add origin $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_HOSTDEPEND)$${EOS_HOSTDIR}.git || echo "Already exist"; \
	elif [ ! -z $${EOS_GITUSER} ] ; then \
	git remote remove origin || echo "No exist"; \
	git remote add origin $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_HOSTDEPEND)$${EOS_HOSTDIR}.git || echo "Already exist"; \
	fi 
	@cd hostdepend/$${EOS_HOSTDIR}/ ; git add -v --all . || echo "No files to be added\n" 

git-add-optional::
	cd optional; git add -v --all . 

git-add-data::
	cd data; git add -v --all . 

git-add-tutorial::
	cd tutorial; git add -v --all . 

git-add-others::
	cd others; git add -v --all . 

git-add-others2::
	cd others2; git add --all . 

#
# Commit
#

git-commit-all:: git-commit git-commit-data git-commit-optional git-commit-tutorial git-commit-others

git-commit:: git-commit-hostdepend
	@git commit || echo "Already commited" 

git-commit-hostdepend::
	@cd hostdepend/$${EOS_HOSTDIR}/ ; git commit || echo "Already commited"  

git-commit-optional::
	cd optional; git commit  

git-commit-data::
	cd data; git commit 

git-commit-tutorial::
	cd tutorial; git commit 

git-commit-others::
	cd others; git commit 

git-commit-others2::
	cd others2; git commit 

git-backup::
	git push $(EOS_GIT_BACKUPSITE) master  --tags

#
# tag
#

git-tag::
	@export DIRECTORYNAME=./; \
	make git-tag-common;

git-tag-optional::
	@export DIRECTORYNAME=optional; \
	make git-tag-common;

git-tag-data::
	@export DIRECTORYNAME=data; \
	make git-tag-common;

git-tag-tutorial::
	@export DIRECTORYNAME=tutorial; \
	make git-tag-common;

git-tag-others::
	@export DIRECTORYNAME=others; \
	make git-tag-common;

git-tag-common::
	@if [ ! -z "$$DIRECTORYNAME" ]; then \
		cd $$DIRECTORYNAME; \
		echo; \
		git tag | sort -k 2,2 -n -t p ; \
		echo -n "Version No. (e.g. vXX.YY.ZZpSSSS) : "; \
		read TTT; \
		if [ ! -z "$$TTT" ]; then \
			git tag $$TTT; \
		else \
			echo "Incorrect."; \
		fi; \
	fi;

#
# push
# 

git-push-all:: git-push git-push-data git-push-optional git-push-tutorial git-push-others

git-push::git-push-hostdepend
#	git push origin master  --tags
	@echo "base"
	@export DIRECTORYNAME=./; \
	export ORIGINNAME=origin; \
	make git-push-with-check;

git-push-hostdepend::
	@#git subtree push --prefix=hostdepend/$${EOS_HOSTDIR}/ --squash hostdepend$${EOS_HOSTDIR} master 
	@echo "hostdepend"
	@#cd hostdepend/$${EOS_HOSTDIR}/;  git push hostdepend$${EOS_HOSTDIR} master 
	@cd hostdepend/$${EOS_HOSTDIR}/;  git push || git push --set-upstream origin master || git push hostdepend$${EOS_HOSTDIR} master 

git-push-optional::
#	cd optional; git push optional master --tags
	@export DIRECTORYNAME=optional; \
	export ORIGINNAME=optional; \
	make git-push-with-check;

git-push-data::
#	cd data; git push data master --tags
	@export DIRECTORYNAME=data; \
	export ORIGINNAME=data; \
	make git-push-with-check;

git-push-tutorial::
#	cd tutorial; git push tutorial master --tags
	@export DIRECTORYNAME=tutorial; \
	export ORIGINNAME=tutorial; \
	make git-push-with-check;

git-push-others::
#	cd others; git push others master --tags
	@export DIRECTORYNAME=others; \
	export ORIGINNAME=others; \
	make git-push-with-check;

git-push-with-check::
	@if [ ! -z "$$DIRECTORYNAME" -a ! -z "$$ORIGINNAME" ]; then \
		cd $$DIRECTORYNAME; \
		echo; \
		SSS=`git tag | sort -k 2,2 -n -t p | tail -1`; \
		if [ ! -z "$$SSS" ]; then \
			echo "$$SSS is Current Tags in $$ORIGINNAME."; \
			echo -n "Was the current tag updated? [ Y|y | N|n ]: "; \
			read TTT; \
			if [ "$$TTT" = Y -o "$$TTT" = y ]; then \
				git push $$ORIGINNAME master --tags; \
			else \
				echo "not push."; \
			fi; \
		else \
			echo "Tags do not exist in $$ORIGINNAME."; \
			echo "Before push please add tag at current repositry."; \
		fi; \
	fi;

#
# fetch
#
git-fetch-all:: git-fetch fit-fetch-zephyr git-fetch-data git-fetch-optional git-fetch-tutorial git-fetch-others

git-fetch::git-pull-hostdepend
	@echo "fetch: base directory" 
	@cd .       ; git fetch origin master --tags 	; git log -1 || echo "No files to be fetched"

git-pull-hostdepend::
	@#git subtree pull --prefix=hostdepend/$${EOS_HOSTDIR}/ --squash hostdepend$${EOS_HOSTDIR} master 
	@echo "pull: hostdepend directory"
	@#cd hostdepend/$${EOS_HOSTDIR}/; git pull --unshallow hostdepend$${EOS_HOSTDIR} master || echo "No files to be fetched" 
	@cd hostdepend/$${EOS_HOSTDIR}/; git pull hostdepend$${EOS_HOSTDIR} master || echo "No files to be fetched" 

git-fetch-zephyr::
	cd zephyr; git fetch zephyr master --tags		; git log -1

git-fetch-data::
	cd data    ; git fetch data master --tags		; git log -1

git-fetch-optional::
	cd optional; git fetch optional master --tags	; git log -1

git-fetch-tutorial::
	cd tutorial; git fetch tutorial master --tags	; git log -1

git-fetch-others::
	cd others  ; git fetch others master --tags		; git log -1

#
# merge
#
git-merge-all:: git-merge git-merge-zephyr git-merge-data git-merge-optional git-merge-tutorial git-merge-others

git-merge::
	#cd .       ; git log -1; git merge FETCH_HEAD 
	cd .       ; git log -1; git merge 

git-merge-zephyr::
	#cd zephyr  ; git log -1; git merge FETCH_HEAD 
	cd zephyr  ; git log -1; git merge 

git-merge-data::
	#cd data    ; git log -1; git merge FETCH_HEAD 
	cd data    ; git log -1; git merge 

git-merge-optional::
	#cd optional; git log -1; git merge FETCH_HEAD
	cd optional; git log -1; git merge 

git-merge-tutorial::
	#cd tutorial; git log -1; git merge FETCH_HEAD 
	cd tutorial; git log -1; git merge 

git-merge-others::
	#cd others  ; git log -1; git merge FETCH_HEAD 
	cd others  ; git log -1; git merge 

#
# Nickname 
#

# init
git-init-all:: git-init git-init-zephyr git-init-data git-init-optional git-init-tutorial git-init-others

git-init:: git-add-hostdepend
	if [ ! -d .git ] ; then git init	; fi
	@export ORIGINNAME=origin; \
	make git-remote-add;

git-init-data::
	if [ ! -d data ] ; then mkdir data; fi
	cd data; \
	if [ ! -d .git ] ; then git init	; fi ;
	@export ORIGINNAME=data; \
	make git-remote-add-data;

git-init-zephyr::
	if [ ! -d zephyr ] ; then mkdir zephyr ; fi
	cd zephyr; \
	if [ ! -d .git ] ; then git init	; fi ;
	@export ORIGINNAME=zephyr; \
	make git-remote-add-zephyr;

git-init-pione::
	if [ ! -d pione ] ; then mkdir pione; fi
	cd pione; \
	if [ ! -d .git ] ; then git init	; fi ;
	@export ORIGINNAME=pione; \
	make git-remote-add-pione;

git-init-optional::
	if [ ! -d optional ] ; then mkdir optional; fi
	if [ ! -L doc      ] ; then ln -sf optional/doc . ; fi
	if [ ! -L objects  ] ; then ln -sf optional/objects . ; fi
	cd optional; \
	if [ ! -d .git ] ; then git init	; fi ;
	@export ORIGINNAME=optional; \
	make git-remote-add-optional;

git-init-tutorial::
	if [ ! -d tutorial ] ; then mkdir tutorial ; fi
	cd tutorial; \
	if [ ! -d .git ] ; then git init	; fi ;
	@export ORIGINNAME=tutorial; \
	make git-remote-add-tutorial;

git-init-others::
	if [ ! -d others ] ; then mkdir others; fi
	cd others ; \
	if [ ! -d .git ] ; then git init	; fi ;
	@export ORIGINNAME=others; \
	make git-remote-add-others;

git-init-others2::
	if [ ! -d others2 ] ; then mkdir others2; fi
	cd others2 ; git remote add others2 $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_OTHERS)

# clone

git-clone-all:: git-clone
	@if [ ! -z "$${EOS_HOME}" -a -d "$${EOS_HOME}" ] ; then \
		cd $${EOS_HOME} ; \
		make git-clone-data git-clone-optional git-clone-tutorial git-clone-others; \
	fi;

git-clone::
	@if [ ! -z "$${EOS_HOME}" -a -d "$${EOS_HOME}" ] ; then \
		TMPDIRECTORY=$$(pwd) ; \
		cd $${EOS_HOME} ; \
		if [ ! -d  .git ] ; \
		then \
			if [ -z $${EOS_GITUSER} ] ; then \
				git clone --depth 1 $(EOS_GIT_REPOSITRY_NOUSER) ./ ; \
			else \
				git clone --depth 1 $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY) ./ ; \
			fi ; \
			cd $${TMPDIRECTORY}; \
			export ORIGINNAME=origin; \
			make git-remote-add; \
		fi; \
	fi;

git-clone-zephyr::
	if [ ! -d zephyr] ; then mkdir zephyr; fi
	@cd zephyr;  if [ ! -d .git ] ; \
	then \
		if [ -z $${EOS_GITUSER} ] ; then \
			git clone --depth 1 $(EOS_GIT_REPOSITRY_ZEPHYR_NOUSER) ./ ; \
		else \
			git clone --depth 1 $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_ZEPHYR) ./; \
		fi ; \
		cd ../ ; \
		export ORIGINNAME=zephyr; \
		make git-remote-add-zephyr; \
	fi

git-clone-data::
	if [ ! -d data ] ; then mkdir data; fi
	@cd data;  if [ ! -d .git ] ; \
	then \
		if [ -z $${EOS_GITUSER} ] ; then \
			git clone --depth 1 $(EOS_GIT_REPOSITRY_DATA_NOUSER) ./ ; \
		else \
			git clone --depth 1 $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_DATA) ./; \
		fi ; \
		cd ../ ; \
		export ORIGINNAME=data; \
		make git-remote-add-data; \
	fi

git-clone-optional::
	if [ ! -d optional ] ; then mkdir optional; fi
	if [ ! -L doc      ] ; then ln -sf optional/doc . ; fi
	if [ ! -L objects  ] ; then ln -sf optional/objects . ; fi
	@cd optional; if [ ! -d .git ] ; \
	then \
		if [ -z $${EOS_GITUSER} ] ; then \
			git clone --depth 1 $(EOS_GIT_REPOSITRY_OPTIONAL_NOUSER) ./ ; \
		else \
			git clone --depth 1 $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_OPTIONAL) ./ ; \
		fi ; \
		cd ../ ; \
		export ORIGINNAME=optional; \
		make git-remote-add-optional; \
	fi

git-clone-tutorial::
	if [ ! -d tutorial ] ; then mkdir tutorial ; fi
	@cd tutorial; if [ ! -d .git ] ; \
	then \
		if [ -z $${EOS_GITUSER} ] ; then \
			git clone --depth 1 $(EOS_GIT_REPOSITRY_TUTORIAL_NOUSER) ./ ; \
		else \
			git clone --depth 1 $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_TUTORIAL) ./ ; \
		fi; \
		cd ../ ; \
		export ORIGINNAME=tutorial; \
		make git-remote-add-tutorial; \
	fi

git-clone-others::
	if [ ! -d others ] ; then mkdir others; fi
	@cd others ; if [ ! -d .git ] ; \
	then \
		if [ -z $${EOS_GITUSER} ] ; then \
			git clone --depth 1 $(EOS_GIT_REPOSITRY_OTHERS_NOUSER) ./ ; \
		else \
			git clone --depth 1 $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_OTHERS) ./ ; \
		fi; \
		cd ../ ; \
		export ORIGINNAME=others; \
		make git-remote-add-others; \
	fi
#
# add
#
git-remote-add::
	@if [ ! -z "$$ORIGINNAME" -a ! -z "$${EOS_HOME}" -a -d "$${EOS_HOME}"  ]; then \
		cd $${EOS_HOME}; \
		SSS=`git remote -v | awk '{print $$1}' | grep origin`; if [ ! -z "$$SSS" ] ; then git remote rm origin ; fi ; \
		if [ -z $${EOS_GITUSER} ] ; then \
			git remote add origin    $(EOS_GIT_REPOSITRY_NOUSER); \
		else \
			git remote add origin    $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY); \
		fi ; \
	fi;

git-remote-add-zephyr::
	@if [ ! -z "$$ORIGINNAME" ]; then \
		cd $$ORIGINNAME; \
		SSS=`git remote -v | awk '{print $$1}' | grep data`; if [ ! -z "$$SSS" ] ; then git remote rm zephyr; fi ; \
		if [ -z $${EOS_GITUSER} ] ; then \
			git remote add zephyr $(EOS_GIT_REPOSITRY_ZEPHYR_NOUSER); \
		else \
			git remote add zephyr $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_ZEPHYR); \
		fi ; \
	fi;

git-remote-add-data::
	@if [ ! -z "$$ORIGINNAME" ]; then \
		cd $$ORIGINNAME; \
		SSS=`git remote -v | awk '{print $$1}' | grep data`; if [ ! -z "$$SSS" ] ; then git remote rm data ; fi ; \
		if [ -z $${EOS_GITUSER} ] ; then \
			git remote add data    $(EOS_GIT_REPOSITRY_DATA_NOUSER); \
		else \
			git remote add data    $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_DATA); \
		fi ; \
	fi;

git-remote-add-optional::
	@if [ ! -z "$$ORIGINNAME" ]; then \
		cd $$ORIGINNAME; \
		SSS=`git remote -v | awk '{print $$1}' | grep optional`; if [ ! -z "$$SSS" ] ; then git remote rm optional ; fi ; \
		if [ -z $${EOS_GITUSER} ] ; then \
			git remote add optional    $(EOS_GIT_REPOSITRY_OPTIONAL_NOUSER); \
		else \
			git remote add optional    $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_OPTIONAL); \
		fi ; \
	fi;

git-remote-add-tutorial::
	@if [ ! -z "$$ORIGINNAME" ]; then \
		cd $$ORIGINNAME; \
		SSS=`git remote -v | awk '{print $$1}' | grep tutorial`; if [ ! -z "$$SSS" ] ; then git remote rm tutorial ; fi ; \
		if [ -z $${EOS_GITUSER} ] ; then \
			git remote add tutorial    $(EOS_GIT_REPOSITRY_TUTORIAL_NOUSER); \
		else \
			git remote add tutorial    $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_TUTORIAL); \
		fi ; \
	fi;

git-remote-add-others::
	@if [ ! -z "$$ORIGINNAME" ]; then \
		cd $$ORIGINNAME; \
		SSS=`git remote -v | awk '{print $$1}' | grep others`; if [ ! -z "$$SSS" ] ; then git remote rm others ; fi ; \
		if [ -z $${EOS_GITUSER} ] ; then \
			git remote add others    $(EOS_GIT_REPOSITRY_OTHERS_NOUSER); \
		else \
			git remote add others    $${EOS_GITUSER}@$(EOS_GIT_REPOSITRY_OTHERS); \
		fi ; \
	fi;
