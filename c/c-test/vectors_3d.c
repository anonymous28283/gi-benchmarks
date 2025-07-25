

vec_3d vector_sub(const vec_3d *a, const vec_3d *b)
{
    vec_3d out;
    out.x = a->x - b->x;
    out.y = a->y - b->y;
    out.z = a->z - b->z;
    return out;
}


vec_3d vector_add(const vec_3d *a, const vec_3d *b)
{
    vec_3d out;
    out.x = a->x + b->x;
    out.y = a->y + b->y;
    out.z = a->z + b->z;

    return out;
}


float dot_prod(const vec_3d *a, const vec_3d *b)
{
    float dot;
    dot = a->x * b->x;
    dot += a->y * b->y;
    dot += a->z * b->z;
    return dot;
}


vec_3d vector_prod(const vec_3d *a, const vec_3d *b)
{
    vec_3d out;

    out.x = a->y * b->z - a->z * b->y;
    out.y = -a->x * b->z + a->z * b->x;
    out.z = a->x * b->y - a->y * b->x;

    return out;
}


const char *print_vector(const vec_3d *a, const char *name)
{
    static char vec_str[100];


    snprintf(vec_str, 99, "vec(%s) = (%.3g)i + (%.3g)j + (%.3g)k\n", name, a->x,
             a->y, a->z);
    return vec_str;
}


float vector_norm(const vec_3d *a)
{
    float n = dot_prod(a, a);
    n = sqrtf(n);
    return n;
}


vec_3d unit_vec(const vec_3d *a)
{
    vec_3d n = {0};

    float norm = vector_norm(a);
    if (fabsf(norm) < EPSILON)
    {
        return n;
    }

    if (norm != 1.F)
    {
        n.x = a->x / norm;
        n.y = a->y / norm;
        n.z = a->z / norm;
    }
    return n;
}


mat_3x3 get_cross_matrix(const vec_3d *a)
{
    mat_3x3 A = {0., -a->z, a->y, a->z, 0., -a->x, -a->y, a->x, 0.};
    return A;
}



double get_angle(const vec_3d *a, const vec_3d *b)
{
    double alpha, cos_alpha;
    float norm_a = vector_norm(a);
    float norm_b = vector_norm(b);
    if (fabsf(norm_a) < EPSILON || fabsf(norm_b) < EPSILON)
    {  
        return NAN; 
    }

    cos_alpha = dot_prod(a, b) / (norm_a * norm_b);
    alpha = acos(cos_alpha);
    return alpha;
}




static void test()
{
    vec_3d a = {1., 2., 3.};
    vec_3d b = {1., 1., 1.};
    float d;




    d = vector_norm(&a);

    assert(fabsf(d - 3.742f) < 0.01);
    d = vector_norm(&b);

    assert(fabsf(d - 1.732f) < 0.01);

    d = dot_prod(&a, &b);

    assert(fabsf(d - 6.f) < 0.01);

    vec_3d c = vector_prod(&a, &b);


    assert(fabsf(c.x - (-1.f)) < 0.01);
    assert(fabsf(c.y - (2.f)) < 0.01);
    assert(fabsf(c.z - (-1.f)) < 0.01);

    double alpha = get_angle(&a, &b);

    assert(fabsf(alpha - 0.387597) < 0.01);
}


int main(void)
{
    test();

    return 0;
}
