#include <clang-c/Index.h>
#include <iostream>

int main(void) {
  CXIndex index = clang_createIndex(0,0);
  CXTranslationUnit tu = clang_createTranslationUnitFromSourceFile(index, "main.cpp", 0 , NULL, 0, 0);

  CXCodeCompleteResults* results = clang_codeCompleteAt(tu,
                                                        "main.cpp",
                                                        4, 7,
                                                        NULL,
                                                        0,
                                                        0);

  if (!results) {
    std::cerr << "can't open" << std::endl;
    return -1;
  }

  for (unsigned i = 0; i < results->NumResults; ++i) {
    const CXCompletionString& str = results->Results[i].CompletionString;

    for (unsigned j = 0; j < clang_getNumCompletionChunks(str); ++j) {
            const CXString& out = clang_getCompletionChunkText(str, j);
            std::cout << clang_getCString(out) << " ";
    }
    std::cout << std::endl;
  }

  clang_disposeCodeCompleteResults(results);
  clang_disposeTranslationUnit(tu);
  clang_disposeIndex(index);
  return 0;
}
