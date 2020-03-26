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
    inspectedModule = None
    moduleHierachy = sys.argv[2:]
    moduleHierachy.reverse()
    for moduleStep in moduleHierachy:
        #print("\n {0} \n\n".format(moduleStep))
        inspectedModule = importlib.import_module(moduleStep,inspectedModule)

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

def importModule():
    returnDict = {
        "name": "unknown",
        "functions":[],
        "classes":[],
        "variables":[]
    }
    inspectedModule = None
    moduleHierachy = sys.argv[2:]
    moduleHierachy.reverse()
    for moduleStep in moduleHierachy:
        #print("\n {0} \n\n".format(moduleStep))
        inspectedModule = importlib.import_module(moduleStep,inspectedModule)
    returnDict["name"] = inspectedModule.__name__
    module_members = inspect.getmembers(inspectedModule)
    for m_member in module_members:
        #TODO preprocess Type to be Compatible with Cross Language Graph
        #TODO search for items in __dir__ or __all__
        member_obj = {}
        if inspect.isfunction(m_member[1]) or inspect.isbuiltin(m_member[1]):
            member_obj["name"] = m_member[0]
            returnDict["functions"].append(member_obj)
            #TODO get the signature of the function after implementing import function
        elif inspect.isclass(m_member[1]):
            member_obj["name"] = m_member[0]
            returnDict["classes"].append(member_obj)
            #TODO add the class options after implementing the variables and the functions
        else:
            member_obj["name"] = m_member[0]
            returnDict["variables"].append(member_obj)
            #TODO get the variable characteristiques  after implementing import variable
    inspectJson = json.dumps(returnDict)
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
     "inspectModule":inspect_entered_module,
     "importModule":importModule
}

## select the operation
if len(sys.argv)>1:
    call = str(sys.argv[1])
    operation_map[call]()

