{"name": "unknown", "template": "/***************************************************************************\n *                                                                         *\n *   Copyright (C) 2020                                                  *\n *                                                                         *\n *   Authors:  Yasser Grimes                                               *\n *   Develeped as a Graduation Project                                     *\n *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *\n *   Supervisor: Bendaoud Faysal                                           *\n ***************************************************************************/\n#ifndef BP_{{nodeName|upper}}_H\n#define BP_{{nodeName|upper}}_H\n\n#include \"bp_{{parentClass|lower}}.h\"\n\n#include <QGraphicsProxyWidget>\n#include <QObject>\n{%if useWidget%}#include <{{widgetClass}}>{%endif%}\n\nclass BP_{{nodeName}} : public BP_{{parentClass}}\n{\n    Q_OBJECT\n    Q_CLASSINFO(\"name\",\"{{nameString}}\")\n    {%if useWidget %}{{widgetClass}} *m_{{widgetInstanceName}};{%endif%}\n    QGraphicsProxyWidget *m_{{nameString|lower}}Item;\npublic:\n    Q_INVOKABLE BP_{{nodeName}}();\n    ~ BP_{{nodeName}}();\n\n    static int nodeTypeID ;\n\npublic slots:\n    void {{widgetValueChangedSlot}};\n    // QGraphicsItem interface\npublic:\n    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;\n    virtual void calculateBounds() override;\n\n    // BP_Node interface\npublic:\n    virtual QString renderNode(BP_PlatformManager *platform) override;\n    QString getNodeTypeString() override;\n};\n\n#endif // BP_{{nodeName|upper}}_H\n\n\n//the c++ file\n\n/***************************************************************************\n *                                                                         *\n *   Copyright (C) 2020                                                  *\n *                                                                         *\n *   Authors:  Yasser Grimes                                               *\n *   Develeped as a Graduation Project                                     *\n *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *\n *   Supervisor: Bendaoud Faysal                                           *\n ***************************************************************************/\n#include \"bp_{{nodeName|lower}}.h\"\n\n#include <QPainter>\n#include <QSpinBox>\n\n#include <Core/bp_variable.h>\n\n#include <Graph/Slots/bp_dataslot.h>\n\n#include <Platform/bp_platformmanager.h>\n\n#include \"Graph/bp_graphutils.h\"\n\nRegisterToolNodeType(BP_{{nodeName}},{{category}})\n\nBP_{{nodeName}}::BP_{{nodeName}}():BP_{{parentClass}}(),\n{%if useWidget%}m_{{widgetInstanceName}}(new {{widgetClass}}()){%endif%},\nm_{{nameString|lower}}Item(new QGraphicsProxyWidget())\n{\n    connect(m_{{widgetInstanceName}},SIGNAL(valueChanged(valueChangedType)),this,SLOT({{widgetValueChangedSlot}}));\n\n    qDebug(\"{{nodeName}} created\");\n    m_{{nameString|lower}}Item->setParentItem(this);\n    m_{{nameString|lower}}Item->setWidget(m_{{widgetInstanceName}});\n    m_{{nameString|lower}}Item->setPos(0,0);\n    m_{{nameString|lower}}Item->setGeometry(QRectF(3,3,70,24));\n\n    //creating the variable\n    BP_Variable *variable = new BP_Variable(nullptr,this);\n    variable->setValue({{variableValue}});\n    variable->setIsMember(false);\n    variable->setIsPrimitive({{isPrimitive}});\n    variable->setName(\"var_{{nameString|lower}}\"+QString::number(nodeId));\n    variable->setIsArray({{isArray}});\n\n    setCoreObject(variable);\n    setVariableObject(variable);\n}\n\nBP_{{nodeName}}::~BP_{{nodeName}}()\n{\n\n}\n\nvoid BP_{{nodeName}}::{{widgetValueChangedSlot}}\n{\n    variableObject()->setValue(value);\n}\n\nvoid BP_{{nodeName}}::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)\n{\n    painter->setBrush(QColor(\"orange\"));\n    painter->drawRect(boundingRect());\n}\n\nvoid BP_{{nodeName}}::calculateBounds()\n{\n    m_bounds.setWidth(100);\n    m_bounds.setHeight(30);\n    m_bounds.setTopLeft(QPoint(0,0));\n    outputSlot()->setPos(m_bounds.width()-17,5);\n}\n\nQString BP_{{nodeName}}::renderNode(BP_PlatformManager *platform)\n{\n    CHECK_FIRST_REFERENCE\n    return platform->render{{nodeName}}(this);\n}\n\nQString BP_{{nodeName}}::getNodeTypeString()\n{\n    return \"{{nameString|lower}}\";\n}\n\n", "values": "nodeName : BoolNode\nparentClass: VariableNode\nnameString: Bool\nuseWidget: true\nwidgetClass: QCheckBox\nwidgetInstanceName: boolCheckBox\nwidgetClassPureName: Checkbox\nwidgetValueChangedSlot: onCheckedChange(bool value)\nvalueChangedType: bool\ncategory: Add Variable\nvariableValue: \"false\"\nisPrimitive: \"true\"\nisArray: \"false\"\nwidth: 100\nheight: 40\n"}