// main.c
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "codegen.h"
#include "ast.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source.simple> <output.c>\n", argv[0]);
        return 1;
    }

    // Read the source file
    const char *source_file = argv[1];
    FILE *src = fopen(source_file, "r");
    if (!src) {
        perror("Error opening source file");
        return 1;
    }

    // Determine the size of the source file
    fseek(src, 0, SEEK_END);
    long length = ftell(src);
    fseek(src, 0, SEEK_SET);

    // Read the file into a buffer
    char *source_code = (char*)malloc(length + 1);
    if (!source_code) {
        perror("Memory allocation failed");
        fclose(src);
        return 1;
    }
    fread(source_code, 1, length, src);
    source_code[length] = '\0';
    fclose(src);

    // Parse the source code
    Parser parser;
    init_parser(&parser, source_code);
    ASTNode *ast = parse_program(&parser);

    // Generate C code
    const char *output_file = argv[2];
    FILE *out = fopen(output_file, "w");
    if (!out) {
        perror("Error creating output file");
        free_ast(ast);
        free(source_code);
        return 1;
    }

    // Write the necessary includes and main function
    fprintf(out, "#include <stdio.h>\n\nint main() {\n");

    // Generate code from AST
    generate_code(ast, out);

    fprintf(out, "    return 0;\n}\n");
    fclose(out);

    // Clean up
    free_ast(ast);
    free(source_code);

    printf("Compilation successful. Output written to %s\n", output_file);
    return 0;
}
