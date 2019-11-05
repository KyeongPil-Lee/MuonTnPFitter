import os

# -- setup

scriptName = "ExtractEfficiencyGraph_count.py"

list_trigger = ["IsoMu24", "Mu50"]
list_year = ["2016_beforeFix", "2016_afterFix", "2017", "2018"]

# -- starting directory with scriptName
baseDir = os.getcwd()

for trigger in list_trigger:
    for year in list_year:

        os.chdir(baseDir)

        dirPath = "%s/%s/%s" % (baseDir, trigger, year)

        cmd_cp = "cp %s %s" % (scriptName, dirPath)
        print "cmd_cp: %s" % cmd_cp

        # -- copy the script to the target dir
        # os.system(cmd_cp)

        os.chdir(dirPath)
        print "move to %s" % dirPath

        cmd_run = "python %s" % scriptName
        print "cmd_run: %s" % cmd_run

        # -- run the script
        # os.system(cmd_run)

        print "[%s/%s] done\n\n" % (trigger, year)
