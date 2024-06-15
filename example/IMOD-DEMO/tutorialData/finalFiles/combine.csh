nohup
if (-e combine.log) \mv -f combine.log combine.log~
if ($?IMOD_DIR) then
    setenv PATH "$IMOD_DIR/bin:$PATH"
endif
echo2 Shell PID: $$
echo "This is the master log file for combine.com"  > combine.log
echo "It will end with COMBINE SUCCESSFULLY COMPLETED upon success" >> combine.log
echo "Look in individual log files for the results of particular operations" >> combine.log
echo " " >> combine.log
goto solvematch >> combine.log
solvematch: >> combine.log
set process = solvematch >> combine.log
echo "Running solvematch.com" >> combine.log
vmstocsh solvematch.log < solvematch.com | csh -ef >> combine.log
if ($status) goto error >> combine.log
matchvol1: >> combine.log
set process = matchvol1 >> combine.log
echo "Initial registration found, next running matchvol1.com" >> combine.log
vmstocsh matchvol1.log < matchvol1.com | csh -ef >> combine.log
if ($status) goto error >> combine.log
patchcorr: >> combine.log
set process = patchcorr >> combine.log
echo "Matchvol finished, next running patchcorr.com" >> combine.log
vmstocsh patchcorr.log < patchcorr.com | csh -ef >> combine.log
if ($status) goto error >> combine.log
matchorwarp: >> combine.log
set process = matchorwarp >> combine.log
echo "Patchcrawl3d found displacements, next running matchorwarp.com" >> combine.log
vmstocsh matchorwarp.log < matchorwarp.com | csh -ef >> combine.log
if ($status) goto error >> combine.log
goto volcombine >> combine.log
warpvol: >> combine.log
set process = warpvol >> combine.log
vmstocsh warpvol.log < warpvol.com | csh -ef >> combine.log
if ($status) goto error >> combine.log
goto volcombine >> combine.log
matchvol2: >> combine.log
set process = matchvol2 >> combine.log
vmstocsh matchvol2.log < matchvol2.com | csh -ef >> combine.log
if ($status) goto error >> combine.log
goto volcombine >> combine.log
volcombine: >> combine.log
set process = volcombine >> combine.log
echo "Matchvol or Warpvol finished, next running volcombine.com" >> combine.log
vmstocsh volcombine.log < volcombine.com | csh -ef >> combine.log
if ($status) goto error >> combine.log
echo "COMBINE SUCCESSFULLY COMPLETED" >> combine.log
exit 0 >> combine.log
error: >> combine.log
echo "ERROR: $process.com failed" >> combine.log
exit 1 >> combine.log
