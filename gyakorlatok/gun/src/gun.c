#include <obj/load.h>

int main(int argc, char* argv[])
{
    Model model;

    load_model(&model, "gun.obj");
    print_model_info(&model);
    print_bounding_box(&model);

    return 0;
}