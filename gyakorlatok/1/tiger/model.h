#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define INVALID_VERTEX_INDEX 0

struct TokenArray
{
    char** tokens;
    int n_tokens;
};

struct Vertex
{
    double x;
    double y;
    double z;
};

struct TextureVertex
{
    double u;
    double v;
};

struct FacePoint
{
    int vertex_index;
    int texture_index;
    int normal_index;
};

struct Triangle
{
    struct FacePoint points[3];
};

struct Quad
{
    struct FacePoint points[4];
};

struct Model
{
    int n_vertices;
    int n_texture_vertices;
    int n_normals;
    int n_triangles;
    int n_quads;
    struct Vertex* vertices;
    struct TextureVertex* texture_vertices;
    struct Vertex* normals;
    struct Triangle* triangles;
    struct Quad* quads;
};

/**
 * Count the tokens in the text.
 */
int count_tokens(const char* text);

/**
 * Calculate the length of the token.
 */
int calc_token_length(const char* text, int start_index);

/**
 * Create the copy of the token from the given string.
 */
char* copy_token(const char* text, int offset, int length);

/**
 * Insert token to the token structure.
 */
void insert_token(const char* token, struct TokenArray* token_array);

/**
 * Extract tokens from text.
 */
void extract_tokens(const char* text, struct TokenArray* token_array);

/**
 * Release the allocate memory of the token array.
 */
void free_tokens(struct TokenArray* token_array);

/**
 * Load OBJ model from file.
 */
int load_model(const char* filename, struct Model* model);

/**
 * Print the information about the loaded model.
 */
void print_model_info(const struct Model* model);

/**
 * Release the allocated memory of the model.
 */
void free_model(struct Model* model);

/**
 * Count the elements in the model and set counts in the structure.
 */
void count_elements(FILE* file, struct Model* model);

/**
 * Read the elements of the model and fill the structure with values.
 */
void read_elements(FILE* file, struct Model* model);

/**
 * Initializes model counters to zero.
 */
void init_model_counters(struct Model* model);

/**
 * Clear the comment from the end of the line.
 */
void clear_comment(char* line);

/**
 * Determine the type of the line and increment the appropriate counter.
 */
void count_element_in_line(const char* line, struct Model* model);

/**
 * Read the given data from the line.
 */
void read_element_from_line(const char* line, struct Model* model);

/**
 * Allocate memory for the model.
 *
 * The OBJ file format starts indices from 1. From this reason,
 * the vertices, texture vertices and normals have a blank 0 element.
 */
void create_arrays(struct Model* model);

/**
 * Read vertex data.
 */
void read_vertex(const struct TokenArray* token_array, struct Vertex* vertex);

/**
 * Read texture vertex data.
 */
void read_texture_vertex(const struct TokenArray* token_array, struct TextureVertex* texture_vertex);

/**
 * Read normal vector data.
 */
void read_normal(const struct TokenArray* token_array, struct Vertex* normal);

/**
 * Read triangle data.
 */
void read_triangle(const struct TokenArray* token_array, struct Triangle* triangle);

/**
 * Read quad data.
 */
void read_quad(const struct TokenArray* token_array, struct Quad* quad);

/**
 * Read face point data.
 */
void read_face_point(const char* text, struct FacePoint* face_point);

/**
 * Count the delimiters in the face token.
 */
int count_face_delimiters(const char* text);

/**
 * Read the next index from the string.
 *
 * It also calculate the length of the number and returns in length.
 */
int read_next_index(const char* text, int* length);

/**
 * Check that the next number is a number digit.
 */
int is_digit(char c);

/**
 * Check that the indices in the triangle are valid.
 */
int is_valid_triangle(const struct Triangle* triangle, const struct Model* model);

/**
 * Check that the indices in the quad are valid.
 */
int is_valid_quad(const struct Quad* quad, const struct Model* model);

/**
 * Calculate the normal vectors.
 */
void calc_normals(struct Model* model);

/**
 * Apply the triangle normals to the vertex normals.
 */
void apply_triangle_normals(struct Model* model);

/**
 * Apply the quad normals to the vertex normals.
 */
void apply_quad_normals(struct Model* model);

/**
 * Normalize the vertex normal vectors.
 */
void normalize_vertex_normals(struct Model* model);

/**
 * Calculate the normal vector of a triangle.
 */
void calc_triangle_normal(
    const struct Vertex* a,
    const struct Vertex* b,
    const struct Vertex* c,
    struct Vertex* n);

/**
 * Calculate the length of the vector.
 */
double calc_length(const struct Vertex* v);

/**
 * Print the bounding box of the model.
 */
void print_bounding_box(const struct Model* model);

/**
 * Scale the loaded model.
 */
void scale_model(struct Model* model, double sx, double sy, double sz);

#endif // MODEL_H
