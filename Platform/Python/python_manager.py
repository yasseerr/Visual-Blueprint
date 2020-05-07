import pydoc
import json
import sys
import importlib
import inspect
## Operations On python env

PRIMITIVE_TYPES = [int, float ,bool ,str]
LIST_TYPES = [list,tuple,set]


NONE_CLASS_TYPES = PRIMITIVE_TYPES + LIST_TYPES

def listGlobalModules():
    #TODO import bultin functions
    globalModules = []
    for module in pydoc.pkgutil.iter_modules():
        globalModules += [module[1]]
    modulesJson = json.dumps(globalModules)
    sys.stdout.write('001')
    sys.stdout.write(writeIntToStdout(len(modulesJson),9))
    sys.stdout.write(modulesJson)
    sys.stdout.flush()

###__________________________IMPORTING MODULES SECTION_____________________________________________

def inspect_entered_module():
    #TODO get the modules using pkgutil.iter_modules(module.__spec__.submodule_search_location)
    #TODO exclude reimported modules
    returnList = []
    inspectedModule = None
    moduleHierachy = sys.argv[2:]
    moduleHierachy.reverse()
    inspectedModule = getModuleFromHiearchy(moduleHierachy)

    module_members = inspect.getmembers(inspectedModule)
    for m_member in module_members:
        #TODO preprocess Type to be Compatible with Cross Language Graph
        #TODO use isFunction is isClass instead of type(in addition to type)
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
    inspectedModule = None
    moduleHierachy = sys.argv[2:]
    moduleHierachy.reverse()
    inspectedModule = getModuleFromHiearchy(moduleHierachy)

    module_name = inspectedModule.__name__
    moduleDict = getModuleDict(inspectedModule,module_name)
    inspectJson = json.dumps(moduleDict)
    sys.stdout.write('002')
    sys.stdout.write(writeIntToStdout(len(inspectJson), 9))
    sys.stdout.write(inspectJson)
    sys.stdout.flush()

def getModuleDict(module_obj,module_name):
    moduleDict = {
        "name": module_name,
        "functions": [],
        "classes": [],
        "variables": []
    }
    module_members = inspect.getmembers(module_obj)
    for m_member in module_members:
        #TODO preprocess Type to be Compatible with Cross Language Graph
        #TODO search for items in __dir__ or __all__
        member_obj = {}
        if inspect.isfunction(m_member[1]) or inspect.isbuiltin(m_member[1]):
            member_obj = getFunctionDict(m_member[1],m_member[0])
            moduleDict["functions"].append(member_obj)
            #TODO get the signature of the function after implementing import function
        elif inspect.isclass(m_member[1]):
            member_obj = getClassDict(m_member[1],m_member[0])
            moduleDict["classes"].append(member_obj)
            #TODO add the class options after implementing the variables and the functions
        else:
            member_obj = getVariableDict(m_member[1],m_member[0])
            moduleDict["variables"].append(member_obj)
            #TODO get the variable characteristiques  after implementing import variable
    
    return moduleDict


def getModuleFromHiearchy(moduleList:list):
    moduleStr = str.join('.',moduleList)
    inspectedModule = importlib.import_module(moduleStr)
    return inspectedModule

###__________________________IMPORTING CLASSES SECTION_____________________________________________

def importClass():
    #TODO get the parameters from the documentation when failed
    #TODO add support for subclasses
    inspectedModule = None
    moduleHierachy = sys.argv[2:]
    moduleHierachy.reverse()
    className = moduleHierachy[-1]
    inspectedModule = getModuleFromHiearchy(moduleHierachy[:-1])

    module_members = inspect.getmembers(inspectedModule)    
    importedClassTuple = findMemberByName(className,module_members)
    className = importedClassTuple[0]
    classDict = getClassDict(importedClassTuple[1],className)
    
    inspectJson = json.dumps(classDict)
    sys.stdout.write('002')
    sys.stdout.write(writeIntToStdout(len(inspectJson), 9))
    sys.stdout.write(inspectJson)
    sys.stdout.flush()

def getClassDict(class_obj,class_name):
    classDict = {
        "name": class_name,
        "functions": [],
        "variables": [],
        "constructors": [],
        "type":"class"

    }
    #getting the variables and functions
    class_members = inspect.getmembers(class_obj)
    for member_name, member_obj in class_members:
        if inspect.isfunction(member_obj) or inspect.isbuiltin(member_obj):
            if(member_name == "__init__"): continue
            classDict["functions"].append(getFunctionDict(member_obj,member_name))
        else :
            classDict["variables"].append(getVariableDict(member_obj,member_name))
    #setting up the constructor
    functionSignature = inspect.signature(class_obj.__init__)
    constructorDict = {
        "inputs" : [],
        "hasKeyWords": False,
        "hasPositional": False,
    }
    for param_name, parameter in functionSignature.parameters.items():
        if param_name == "self":
            continue
        param_map = {
            "name": param_name,
            "default": "unknown",
            "class": "unknown",
            "constructor": 0,
            "kind": 0 , # 0: for positionl_kw, 1: for kw
        }

        if parameter.kind == inspect.Parameter.POSITIONAL_OR_KEYWORD:
            param_map["class"] = (
                parameter.annotation.__name__ if parameter.annotation is not inspect._empty else "unknown")
            constructorDict["inputs"].append(param_map)
        elif parameter.kind == inspect.Parameter.KEYWORD_ONLY:
            param_map["class"] = (
                parameter.annotation.__name__ if parameter.annotation is not inspect._empty else "unknown")
            param_map["kind"] = 1
            constructorDict["inputs"].append(param_map)
        elif parameter.kind == inspect.Parameter.POSITIONAL_ONLY:
            param_map["class"] = (
                parameter.annotation.__name__ if parameter.annotation is not inspect._empty else "unknown")
            param_map["kind"] = 2
            constructorDict["inputs"].append(param_map)
        elif parameter.kind == inspect.Parameter.VAR_POSITIONAL:
            constructorDict["hasPositional"] = True
        elif parameter.kind == inspect.Parameter.VAR_KEYWORD:
            constructorDict["hasKeyWords"] = True
        #TODO add the default variable dict
    classDict["constructors"].append(constructorDict)

    return classDict



###__________________________IMPORRING Function SECTION_____________________________________________

def importFunction():
    #TODO get the parameters from the documentation when failed
    #TODO support wrapper desctiption
    inspectedModule = None
    moduleHierachy = sys.argv[2:]
    moduleHierachy.reverse()
    functionName = moduleHierachy[-1]
    inspectedModule =  getModuleFromHiearchy(moduleHierachy[:-1])

    module_members = inspect.getmembers(inspectedModule)    
    importedFunctionTuple = findMemberByName(functionName,module_members)
    functionName = importedFunctionTuple[0]
    functionDict = getFunctionDict(importedFunctionTuple[1],functionName)
    
    inspectJson = json.dumps(functionDict)
    sys.stdout.write('002')
    sys.stdout.write(writeIntToStdout(len(inspectJson), 9))
    sys.stdout.write(inspectJson)
    sys.stdout.flush()

def getFunctionDict(function_obj,function_name):
    functionDict = {
        "name": function_name,
        "inputs": [],
        "outputs": [],
        "hasKeyWords": False,
        "hasPositional": False,
        "isFullyImported": False,
        "type":"func"
    }
    if(inspect.isbuiltin(function_obj)):
        #TODO implement help parsing for the builtin functions
        functionDict["hasKeyWords"] = True
        functionDict["hasPositional"] = True
        return functionDict
    functionSignature = inspect.signature(function_obj)
    for param_name, parameter in functionSignature.parameters.items():
        param_map = {
            "name": param_name,
            "default": "unknown",
            "class": "unknown",
            "constructor": 0,
            "kind": 0 , # 0: for positionl_kw, 1: for kw
        }
        #TODO get the constructor for the variable
        if parameter.kind == inspect.Parameter.POSITIONAL_OR_KEYWORD:
            param_map["class"] = (
                parameter.annotation.__name__ if parameter.annotation is not inspect._empty else "unknown")
            functionDict["inputs"].append(param_map)
        elif parameter.kind == inspect.Parameter.KEYWORD_ONLY:
            param_map["class"] = (
                parameter.annotation.__name__ if parameter.annotation is not inspect._empty else "unknown")
            param_map["kind"] = 1
            functionDict["inputs"].append(param_map)
        elif parameter.kind == inspect.Parameter.POSITIONAL_ONLY:
            param_map["class"] = (
                parameter.annotation.__name__ if parameter.annotation is not inspect._empty else "unknown")
            param_map["kind"] = 2
            functionDict["inputs"].append(param_map)
        elif parameter.kind == inspect.Parameter.VAR_POSITIONAL:
            functionDict["hasPositional"] = True
        elif parameter.kind == inspect.Parameter.VAR_KEYWORD:
            functionDict["hasKeyWords"] = True
        #TODO add the default variable dict
    if functionSignature.return_annotation is not inspect._empty:
        returnDict["outputs"].append(
            functionSignature.return_annotation.__name__)

    return functionDict



###__________________________IMPORRING VARIABLES SECTION_____________________________________________

def importVariable():
    #TODO get the parameters from the documentation when failed
    inspectedModule = None
    moduleHierachy = sys.argv[2:]
    moduleHierachy.reverse()
    variableName = moduleHierachy[-1]
    inspectedModule = getModuleFromHiearchy(moduleHierachy[:-1])

    module_members = inspect.getmembers(inspectedModule)    
    importedVariableTuple = findMemberByName(variableName,module_members)
    variableDict = getVariableDict(importedVariableTuple[1],variableName)
    
    inspectJson = json.dumps(variableDict)
    sys.stdout.write('002')
    sys.stdout.write(writeIntToStdout(len(inspectJson), 9))
    sys.stdout.write(inspectJson)
    sys.stdout.flush()
    
def getVariableDict(var_obj,var_name,module_arg=None,class_arg=None):
    returnDict = {
        "name": var_name,
        "value":getVariableValue(var_obj),
        "className":getVariableClass(var_obj),
        "isPrimitive": isPrimitive(var_obj),
        "isArray": isArray(var_obj),
        "classModule":"",#getClassModule(var_obj),
        "type":"var"
    }
    return returnDict


def isPrimitive(obj):
    if type(obj) in PRIMITIVE_TYPES:
        return True
    else:
        return False

def isArray(obj):
    if type(obj) in LIST_TYPES:
        return True
    else:
        return False

def getVariableClass(var_obj):
    if type(var_obj) in NONE_CLASS_TYPES:
        return False
    else:
        return type(var_obj).__name__

def getVariableValue(var_obj):
    if(type(var_obj) in PRIMITIVE_TYPES):
        return var_obj
    else:
        #TODO replace unknown by a uninque string
        return "unknown"

###__________________________Loading builtins SECTION_____________________________________________


def loadBuiltins():
    retList = []
    inspectedModule = importlib.import_module("builtins")

    module_members = inspect.getmembers(inspectedModule)
    #print(len(module_members))
    for memberName,memberObj in module_members:
        #print(memberName)
        retList.append(getObjectDict(memberObj,memberName))
    inspectJson = json.dumps(retList)
    #print(len(inspectJson))
    sys.stdout.write('002')
    sys.stdout.write(writeIntToStdout(len(inspectJson), 9))
    sys.stdout.write(inspectJson)
    sys.stdout.flush()



###_____________________________________Helper_Function________________________________________________


#listGlobalModules()
#inspect_entered_module()
#heping functions

def getObjectDict(obj,name,type=["variable"]):
    obj_dict = {}
    if inspect.isfunction(obj) or inspect.isbuiltin(obj) or inspect.ismethoddescriptor(obj):
        obj_dict = getFunctionDict(obj,name)
        type[0] = 'function'
    elif inspect.isclass(obj):
        obj_dict = getClassDict(obj,name)
        type[0] = 'class'
    else:
        obj_dict = getVariableDict(obj,name)
        type[0] = 'variable'

    return obj_dict

def findMemberByName(name,membersList):
    for x in membersList:
        #print(x[0])
        if name == x[0] : return x
    return None

def writeIntToStdout(n:int,stringSize=3):
    nStr = str(n)
    nStr = (stringSize-len(nStr))*'0'+nStr
    return nStr


#________________________________________Operation_Mapping______________________________________________

operation_map = { 
     "listGM":listGlobalModules,
     "inspectModule":inspect_entered_module,
     "importModule":importModule,
     "importFunction":importFunction,
     "importVariable":importVariable,
     "importClass":importClass,
     "loadBuiltins":loadBuiltins
}

## select the operation
if len(sys.argv)>1:
    call = str(sys.argv[1])
    operation_map[call]()

