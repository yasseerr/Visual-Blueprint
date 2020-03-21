import pydoc
import json
import sys
import importlib
import inspect
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

def inspect_entered_module():
    returnList = []
    moduleName = sys.argv[2]
    #moduleName = "networkx"
    inspectedModule = importlib.import_module(moduleName)
    module_members = inspect.getmembers(inspectedModule)
    for m_member in module_members:
        #TODO preprocess Type to be Compatible with Cross Language Graph
        m_memberItem = {
            "name": m_member[0],
            "type": type(m_member[1]).__name__
        }
        returnList.append(m_memberItem)
    inspectJson = json.dumps(returnList)
    sys.stdout.write('002')
    sys.stdout.write(writeIntToStdout(len(inspectJson), 9))
    sys.stdout.write(inspectJson)
    sys.stdout.flush()
    

#listGlobalModules()
#inspect_entered_module()
#heping functions

def writeIntToStdout(n:int,stringSize=3):
    nStr = str(n)
    nStr = (stringSize-len(nStr))*'0'+nStr
    return nStr


#operation Mapping

operation_map = { 
     "listGM":listGlobalModules,
     "inspectModule":inspect_entered_module
}

## select the operation
if len(sys.argv)>1:
    call = str(sys.argv[1])
    operation_map[call]()

