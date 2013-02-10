OTHER_FILES += $$FLEXSOURCES

# create a qt compiler object for the EXTRA_COMPILERS FLAG
# this flag list the sources we wish to input to this custom compiler
flex.input = FLEXSOURCES
# we need to say what files to output
flex.output = ${QMAKE_FILE_BASE}.cpp
# actual compile command
flex.commands = flex -o ${QMAKE_FILE_IN_BASE}.cpp ${QMAKE_FILE_IN}
# add the output files to the linker stage. in this case add the generated c file to the sources
flex.variable_out = SOURCES
# ensure that the extra compiler is run before the main c one
flex.CONFIG += target_predeps
# remove the c file on clean
flex.clean = ${QMAKE_FILE_IN_BASE}.cpp
# set the name of the extra compiler
flex.name = flex
# add the extra compiler to the project
QMAKE_EXTRA_COMPILERS += flex
# add flex lib

macx: {
    INCLUDEPATH += -I/usr/local/opt/flex/include
    LIBS += -L/usr/local/opt/flex/lib
}


LIBS += -lfl
