#include "game.h"

void init_game(Scene* scene)
{
    int i;
    for (i = 0; i < N_PARTICLES; ++i)
    {
        scene->particles[i] = generate_particle(&(scene->cherry_material));
    }

    drag_distance = 0.0;
    show_help = false;
    in_hole = false;
    shots_taken = 0;
}

void update_game(Scene *scene, double delta)
{
    //printf("Pos: %f %f %f\n", scene->golfball.position.x, scene->golfball.position.y, scene->golfball.position.z);
    //printf("DirVec: %f %f %f\n", scene->golfball.direction_vector.x, scene->golfball.direction_vector.y, scene->golfball.direction_vector.z);
    //printf("Vel: %f\n", scene->golfball.velocity);

    //Basic forces
    if (abs(scene->golfball.velocity) >= abs(scene->golfball.speed))
    {
        scene->golfball.position.x += scene->golfball.speed * delta * scene->golfball.direction_vector.x;
        scene->golfball.position.y += scene->golfball.speed * delta * scene->golfball.direction_vector.y;
        scene->golfball.position.z += scene->golfball.speed * delta * scene->golfball.direction_vector.z;

        scene->golfball.velocity -= scene->golfball.speed * delta;
    }
    else
    {
        scene->golfball.position.x += scene->golfball.velocity * scene->golfball.direction_vector.x;
        scene->golfball.position.y += scene->golfball.velocity * scene->golfball.direction_vector.y;
        scene->golfball.position.z += scene->golfball.velocity * scene->golfball.direction_vector.z;
        scene->golfball.velocity = 0;
    }

    int brick_we_are_standing_on = on_ground(scene);

    if (brick_we_are_standing_on == -1 || brick_we_are_standing_on == scene->hole)
    {
        scene->golfball.direction_vector.z = -1.0f;
        if (scene->golfball.velocity == 0.0)
        {
            scene->golfball.velocity = 1.0;
        }
    }
    else
    {
        scene->golfball.direction_vector.z = 0.0f;
    }

    //Magic fuckery
    if (scene->golfball.velocity < -100000)
        scene->golfball.velocity = 0.0;
    if (scene->golfball.speed > 100000)
        scene->golfball.speed = 2.0f;
    if (abs(scene->golfball.velocity) < 0.001)
        scene->golfball.velocity = 0.0f;

    // Out of Out of Bounds
    if (scene->golfball.position.x > 900 || scene->golfball.position.x < -900 ||
        scene->golfball.position.y > 900 || scene->golfball.position.y < -900 ||
        scene->golfball.position.z < -1.0f || scene->golfball.position.z > 900)
    {
        printf("Ball OOB @ %f %f %f\n", scene->golfball.position.x, scene->golfball.position.y, scene->golfball.position.z);
        reset_ball(&(scene->golfball), true);
    }


    in_hole = false;
    //Check if we are standing still
    if (scene->golfball.velocity == 0.0 && brick_we_are_standing_on > -1)
    {
        scene->golfball.still = true;

        if (brick_we_are_standing_on == 0)
        {
            if (is_colliding_with_brick(scene) != scene->hole)
            {
                reset_ball(&(scene->golfball), false);
            } else
            {
                in_hole = true;
            }
        }
    }
    else
    {
        scene->golfball.still = false;
    }

    stop_colliding(scene);
    prevent_colliding(scene);
    update_particles(scene->particles, &(scene->cherry_material), delta);
}

void make_ball_move(Scene* scene, Camera* camera, double drag_distance)
{
    //Create vector between camera and ball
    vec3 look = create_vec3(
        scene->golfball.position.x - camera->position.x,
        scene->golfball.position.y - camera->position.y,
        scene->golfball.position.z - camera->position.z);

    //Make the velocity the drag distance
    scene->golfball.velocity = drag_distance;

    double cam_dist = sqrt(pow(look.x, 2) + pow(look.y, 2));

    //Normalize the vectors
    look.x = (look.x / cam_dist);
    look.y = (look.y / cam_dist);

    //Set the vectors
    scene->golfball.direction_vector.x = look.x;
    scene->golfball.direction_vector.y = look.y;

    //The direction vector may be inf, if we are looking at the ball from the top, so we just set it to 0
    if (scene->golfball.direction_vector.x > 1)
        scene->golfball.direction_vector.x = 0;
    if (scene->golfball.direction_vector.y > 1)
        scene->golfball.direction_vector.y = 0;
    if (scene->golfball.direction_vector.x < -1)
        scene->golfball.direction_vector.x = 0;
    if (scene->golfball.direction_vector.y < -1)
        scene->golfball.direction_vector.y = 0;
}

void reset_ball(GolfBall *ball, bool reset_strokes)
{
    ball->position.x = 0;
    ball->position.y = 0;
    ball->position.z = 10;
    if (reset_strokes) shots_taken = 0;
}

int on_ground(Scene *scene)
{
    GolfBall *ball = &(scene->golfball);

    int i;
    for (i = 0; i < N_BRICKS; ++i)
    {
        if (
            //From top-down perspective the ball should be on-top
            ball->position.x + 1.0f >= scene->bricks[i].position.x &&
            ball->position.x - 1.0f <= scene->bricks[i].position.x + scene->bricks[i].size.x &&
            ball->position.y + 1.0f >= scene->bricks[i].position.y &&
            ball->position.y - 1.0f <= scene->bricks[i].position.y + scene->bricks[i].size.y &&
            //And from side views should be exacly on-top
            ball->position.z - 1.0f == scene->bricks[i].position.z + scene->bricks[i].size.z)
        {
            return i;
        }
    }
    return -1;
}

void prevent_colliding(Scene *scene)
{
    int colliding_brick = is_going_to_collide_with_brick(scene);
    if (colliding_brick > -1)
    {
        float distance[6];
        calc_distances_from_brick(scene, colliding_brick, distance);
        float min_distance = calc_min_distance(distance);
        kick_from_brick(scene, min_distance, distance, colliding_brick);
    }
}

void stop_colliding(Scene *scene)
{
    int colliding_brick = is_colliding_with_brick(scene);
    if (colliding_brick > -1)
    {
        float distance[6];
        calc_distances_from_brick(scene, colliding_brick, distance);
        float min_distance = calc_min_distance(distance);
        kick_from_brick(scene, min_distance, distance, colliding_brick);
    }
}

void calc_distances_from_brick(Scene *scene, int colliding_brick, float *distance)
{
    distance[0] = scene->golfball.position.x - scene->bricks[colliding_brick].position.x;
    distance[1] = scene->golfball.position.x - (scene->bricks[colliding_brick].position.x + scene->bricks[colliding_brick].size.x);
    distance[2] = scene->golfball.position.y - scene->bricks[colliding_brick].position.y;
    distance[3] = scene->golfball.position.y - (scene->bricks[colliding_brick].position.y + scene->bricks[colliding_brick].size.y);
    distance[4] = scene->golfball.position.z - scene->bricks[colliding_brick].position.z;
    distance[5] = scene->golfball.position.z - (scene->bricks[colliding_brick].position.z + scene->bricks[colliding_brick].size.z);
}

float calc_min_distance(float *distance)
{
    float min_distance = fmin(abs(distance[0]), abs(distance[1]));

    int i;
    for (i = 2; i < 6; ++i)
    {
        min_distance = fmin(min_distance, abs(distance[i]));
    }
    return min_distance;
}

void kick_from_brick(Scene *scene, float min_distance, float *distance, int colliding_brick)
{
    //Don't get kicked our from the hole
    if (colliding_brick == scene->hole) return;

    if (min_distance == abs(distance[0]) || min_distance == abs(distance[1]))
    {
        // Collission on left side
        // Collission on right side

        scene->golfball.direction_vector.x *= -1.0f;

        if (scene->golfball.direction_vector.x < 0)
        {
            scene->golfball.position.x = scene->bricks[colliding_brick].position.x - 1.0f;
        }
        else
        {
            scene->golfball.position.x = scene->bricks[colliding_brick].position.x + scene->bricks[colliding_brick].size.x + 1.0f;
        }
    }
    else if (min_distance == abs(distance[2]) || min_distance == abs(distance[3]))
    {
        //Collission on front side
        //Collission on back side

        scene->golfball.direction_vector.y *= -1.0f;

        if (scene->golfball.direction_vector.y < 0)
        {
            scene->golfball.position.y = scene->bricks[colliding_brick].position.y - 1.0f;
        }
        else
        {
            scene->golfball.position.y = scene->bricks[colliding_brick].position.y + scene->bricks[colliding_brick].size.y + 1.0f;
        }
    }
    else
    {
        //Collision on bottom side
        //Collision on top side
        scene->golfball.direction_vector.z *= 0.0f;

        if (scene->golfball.direction_vector.z < 0)
        {
            scene->golfball.position.z = scene->bricks[colliding_brick].position.z - 1.0f;
        }
        else
        {
            scene->golfball.position.z = scene->bricks[colliding_brick].position.z + scene->bricks[colliding_brick].size.z + 1.0f;
        }
    }
}

int is_colliding_with_brick(Scene *scene)
{
    int i;
    for (i = 0; i < N_BRICKS; ++i)
    {
        if (
            scene->golfball.position.x + 1.0f > scene->bricks[i].position.x &&
            scene->golfball.position.x - 1.0f < scene->bricks[i].position.x + scene->bricks[i].size.x &&
            scene->golfball.position.y + 1.0f > scene->bricks[i].position.y &&
            scene->golfball.position.y - 1.0f < scene->bricks[i].position.y + scene->bricks[i].size.y &&
            scene->golfball.position.z + 1.0f > scene->bricks[i].position.z &&
            scene->golfball.position.z - 1.0f < scene->bricks[i].position.z + scene->bricks[i].size.z)
        {
            return i;
        }
    }
    return -1;
}

int is_going_to_collide_with_brick(Scene *scene)
{
    GolfBall *ball = &(scene->golfball);

    int i;
    for (i = N_BRICKS - 1; i >= 0; --i)
    {
        if (
            ball->position.x + (ball->speed * ball->direction_vector.x) >= scene->bricks[i].position.x &&
            ball->position.x + (ball->speed * ball->direction_vector.x) <= scene->bricks[i].position.x + scene->bricks[i].size.x &&
            ball->position.y + (ball->speed * ball->direction_vector.y) >= scene->bricks[i].position.y &&
            ball->position.y + (ball->speed * ball->direction_vector.y) <= scene->bricks[i].position.y + scene->bricks[i].size.y &&
            ball->position.z + (ball->speed * ball->direction_vector.z) >= scene->bricks[i].position.z &&
            ball->position.z + (ball->speed * ball->direction_vector.z) <= scene->bricks[i].position.z + scene->bricks[i].size.z &&
            ball->velocity != 0)
        {
            return i;
        }
    }
    return -1;
}

bool can_move(Scene* scene, Camera* camera)
{
    return (scene->golfball.still && !in_hole && !camera->freecam);
}

MaterialBrickParticle generate_particle(Material* material)
{
    MaterialBrickParticle particle;
    particle.material = material;
    particle.size = create_vec3(1, 1, 0.1f);
    particle.lifespan = rand() % 600000;
    particle.position = create_vec3((rand() % 200) - 100, (rand() % 200) - 100, (rand() % 25) + 1);
    particle.rotation_angle = rand() % 360;
    particle.speed = create_vec3(((rand() % 100) - 50) / 10, ((rand() % 100) - 50) / 10, ((rand() % 100) - 75) / 10);
    return particle;
}

void update_particles(MaterialBrickParticle* particles, Material* material, float delta)
{
    int i;
    for (i = 0; i < N_PARTICLES; ++i)
    {
        if (particles[i].lifespan > 0 && particles[i].position.z > 0)
        {
            particles[i].lifespan-= delta;
            particles[i].position.x += particles[i].speed.x * delta;
            particles[i].position.y += particles[i].speed.y * delta;
            particles[i].position.z += particles[i].speed.z * delta;
        } else
        {
            particles[i] = generate_particle(material);
        }
    }
}