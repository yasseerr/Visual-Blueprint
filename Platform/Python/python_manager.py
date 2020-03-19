import pydoc
import json
import sys

## Operations On python env

def listGlobalModules():
    globalModules = []
    for module in pydoc.pkgutil.iter_modules():
        globalModules += [module[1]]
    modulesJson = json.dumps(globalModules)
    sys.stdout.write('001')
    sys.stdout.write(writeIntToStdout(len(modulesJson),9))
    sys.stdout.write(modulesJson)
    sys.stdout.flush()

#listGlobalModules()

#heping functions

def writeIntToStdout(n:int,stringSize=3):
    nStr = str(n)
    nStr = (stringSize-len(nStr))*'0'+nStr
    return nStr


#operation Mapping

operation_map = { 
     "listGM":listGlobalModules
}

## select the operation
if len(sys.argv)>1:
    call = sys.argv[1]
    operation_map[call]()


