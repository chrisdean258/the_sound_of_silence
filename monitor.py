import subprocess
import time

folder = "."
command_to_run = "ls -t | head -n 1"
finalcommand = "./dataProcessing "

def get_drlist():
    return subprocess.check_output(["ls", folder]).decode('utf-8').strip().split("\n")

while True:
    drlist1 = get_drlist()
    time.sleep(2)
    drlist2 = get_drlist()
    if len(drlist2) > len(drlist1):
       p = subprocess.check_output(["/bin/bash", "-c", command_to_run])
       finalcommand += p
       subprocess.Popen(["/bin/bash", "-c", finalcommand])
       
