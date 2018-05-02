
#CXX="/usr/bin/c++"
CXX="g++"

LLVM_PATH="/usr/lib/llvm-3.7"

BCC_PATH="/home/zqy/WorkSpace/LabeledKernel/Reference/linux/eBPF/bcc"


CXX_FLAGS="-Wall  -isystem ${LLVM_PATH}/include -O3 -DNDEBUG   -std=gnu++11"

CXX_DEFINES= 

CXX_INCLUDES="-I${LLVM_PATH}/include/../tools/clang/include -I/home/zqy/WorkSpace/LabeledKernel/Reference/linux/eBPF/bcc/src/cc -I/home/zqy/WorkSpace/LabeledKernel/Reference/linux/eBPF/bcc/src/cc/api "



LLVM_LIB="${LLVM_PATH}/lib/libclangFrontend.a ${LLVM_PATH}/lib/libclangSerialization.a ${LLVM_PATH}/lib/libclangDriver.a ${LLVM_PATH}/lib/libclangParse.a ${LLVM_PATH}/lib/libclangSema.a ${LLVM_PATH}/lib/libclangCodeGen.a ${LLVM_PATH}/lib/libclangAnalysis.a ${LLVM_PATH}/lib/libclangRewrite.a ${LLVM_PATH}/lib/libclangEdit.a ${LLVM_PATH}/lib/libclangAST.a ${LLVM_PATH}/lib/libclangLex.a ${LLVM_PATH}/lib/libclangBasic.a ${LLVM_PATH}/lib/libLLVMLTO.a ${LLVM_PATH}/lib/libLLVMX86CodeGen.a ${LLVM_PATH}/lib/libLLVMX86Desc.a ${LLVM_PATH}/lib/libLLVMX86Info.a ${LLVM_PATH}/lib/libLLVMMCDisassembler.a ${LLVM_PATH}/lib/libLLVMX86AsmPrinter.a ${LLVM_PATH}/lib/libLLVMX86Utils.a ${LLVM_PATH}/lib/libLLVMPasses.a ${LLVM_PATH}/lib/libLLVMipo.a ${LLVM_PATH}/lib/libLLVMVectorize.a ${LLVM_PATH}/lib/libLLVMOption.a ${LLVM_PATH}/lib/libLLVMObjCARCOpts.a ${LLVM_PATH}/lib/libLLVMMCJIT.a ${LLVM_PATH}/lib/libLLVMExecutionEngine.a ${LLVM_PATH}/lib/libLLVMRuntimeDyld.a ${LLVM_PATH}/lib/libLLVMLinker.a ${LLVM_PATH}/lib/libLLVMIRReader.a ${LLVM_PATH}/lib/libLLVMAsmParser.a ${LLVM_PATH}/lib/libLLVMDebugInfoDWARF.a ${LLVM_PATH}/lib/libLLVMBPFCodeGen.a ${LLVM_PATH}/lib/libLLVMSelectionDAG.a ${LLVM_PATH}/lib/libLLVMBPFDesc.a ${LLVM_PATH}/lib/libLLVMBPFInfo.a ${LLVM_PATH}/lib/libLLVMBPFAsmPrinter.a ${LLVM_PATH}/lib/libLLVMAsmPrinter.a ${LLVM_PATH}/lib/libLLVMCodeGen.a ${LLVM_PATH}/lib/libLLVMTarget.a ${LLVM_PATH}/lib/libLLVMScalarOpts.a ${LLVM_PATH}/lib/libLLVMProfileData.a ${LLVM_PATH}/lib/libLLVMObject.a ${LLVM_PATH}/lib/libLLVMMCParser.a ${LLVM_PATH}/lib/libLLVMBitReader.a ${LLVM_PATH}/lib/libLLVMInstCombine.a ${LLVM_PATH}/lib/libLLVMInstrumentation.a ${LLVM_PATH}/lib/libLLVMTransformUtils.a ${LLVM_PATH}/lib/libLLVMipa.a ${LLVM_PATH}/lib/libLLVMMC.a ${LLVM_PATH}/lib/libLLVMAnalysis.a ${LLVM_PATH}/lib/libLLVMBitWriter.a ${LLVM_PATH}/lib/libLLVMCore.a ${LLVM_PATH}/lib/libLLVMSupport.a"





/usr/bin/c++  $CXX_DEFINES $CXX_INCLUDES $CXX_FLAGS  -c *.cpp


/usr/bin/c++   -Wall  -isystem ${LLVM_PATH}/include -O3 -DNDEBUG  -rdynamic *.o  -o main ${BCC_PATH}/src/cc/libbcc.a ${BCC_PATH}/src/cc/frontends/b/libb_frontend.a ${BCC_PATH}/src/cc/frontends/clang/libclang_frontend.a ${BCC_PATH}/src/cc/libbpf.a  $LLVM_LIB -lz -lpthread -lffi -ledit -ltinfo -ldl -lm -lelf ${BCC_PATH}/src/cc/api/libapi-static.a ${BCC_PATH}/src/cc/usdt/libusdt-static.a ${BCC_PATH}/src/cc/libbcc-loader-static.a -lelf 

