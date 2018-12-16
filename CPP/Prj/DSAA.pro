TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    ../Array/ \
    ../Common/ \
    ../Graph/ \
    ../List/ \
    ../List/LinkList/ \
    ../List/SeqList/ \
    ../Pointer/ \
    ../Queue/ \
    ../Stack/ \
    ../Tree/

HEADERS += \
    ../Array/Array.h \
    ../Array/DynamicArray.h \
    ../Array/StaticArray.h \
    ../Common/Exception.h \
    ../Common/Object.h \
    ../Common/Standard.h \
    ../Graph/Graph.h \
    ../Graph/ListGraph.h \
    ../Graph/MatrixGraph.h \
    ../List/LinkList/LinkList.h \
    ../List/LinkList/LinuxList.h \
    ../List/LinkList/StaticLinkList.h \
    ../List/SeqList/DynamicList.h \
    ../List/SeqList/SeqList.h \
    ../List/SeqList/StaticList.h \
    ../List/List.h \
    ../Pointer/Pointer.h \
    ../Pointer/SharedPointer.h \
    ../Pointer/SmartPointer.h \
    ../Queue/LinkQueue.h \
    ../Queue/Queue.h \
    ../Stack/LinkStack.h \
    ../Stack/Stack.h \
    ../Stack/StaticStack.h \
    ../Tree/BTree.h \
    ../Tree/BTreeNode.h \
    ../Tree/GTree.h \
    ../Tree/GTreeNode.h \
    ../Tree/Tree.h \
    ../Tree/TreeNode.h

SOURCES += \
    ../Common/Exception.cpp \
    ../Common/Object.cpp \
    ../Test/Graph.cpp \
    ../main.cpp


