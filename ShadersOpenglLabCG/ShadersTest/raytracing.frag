#version 430
#define EPSILON 0.001
#define BIG 1000000.0

//DATA STRUCTURES
struct Camera
{
	vec3 position;
	vec3 view;
	vec3 up;
	vec3 side;
};

struct Ray
{
	vec3 origin;
	vec3 direction;
};

//GEOMETRY

struct Sphere
{
	vec3 center;
	float radius;
	vec3 color;
	int material_idx;
};

struct Triangle
{
	vec3 v1;
	vec3 v2;
	vec3 v3;
	vec3 color;
};

struct Square{
    vec3 v1;
    vec3 v2;
    vec3 v3;
    vec3 v4;
    vec3 color;
	int material_ind;
};

struct Material
{
	//ambient, diffuse, specular
	vec4 light_coeffs;
};

struct Intersection
{
	float time;
	vec3 point;
	vec3 normal;
	vec3 color;
	//ambient, diffuse, specular
	vec4 light_coeffs;
	int material_idx;
};

bool IntersectSphere(Sphere sphere,Ray ray,out float time){
	ray.origin-=sphere.center;
	float A=dot(ray.direction,ray.direction);
	float B=dot(ray.direction,ray.origin);
	float C=dot(ray.origin,ray.origin)-sphere.radius*sphere.radius;
	float D=B*B-A*C; //what

	if(D>0.0){
		D=sqrt(D);
		float t1=(-B-D)/A;	//what
		float t2=(-B+D)/A;	//what

		float min_t=min(t1,t2);
		float max_t=max(t1,t2);

		if(max_t<0){
			return false;
		}

		if(min_t<0){
			time=max_t;
			return true;
		}
		time=min_t;
		return true;
	}
	return false;
}

bool IntersectTriangle (Ray ray, vec3 vertex1, vec3 vertex2, vec3 vertex3, out float time ){
    time = -1;
	//вычисляем 2 вектора
    vec3 A = vertex2 - vertex1;
    vec3 B = vertex3 - vertex1;
	//ищем нормаль через векторное произведение
    vec3 Normal = cross(A, B);
	//скалярное произведение
    float N_and_Ray_DotProduct = dot(Normal, ray.direction);
	//нет пересечения
    if (abs(N_and_Ray_DotProduct) < EPSILON){   
		return false;
	}
	//скалярное произведение
    float d = dot(Normal, vertex1);
    float t = -1. * (dot(Normal, ray.origin) - d) / N_and_Ray_DotProduct;
	//нет пересечения
    if (t < 0) {
		return false;
	}
    vec3 P = ray.origin + t * ray.direction;
    vec3 edge1 = vertex2 - vertex1;
    vec3 diffP_v1 = P - vertex1;
    vec3 C = cross(edge1, diffP_v1);
    if (dot(Normal, C) < 0){  
		return false;
	}
    vec3 edge2 = vertex3 - vertex2;
    vec3 diffP_v2 = P - vertex2;
    C = cross(edge2, diffP_v2);
	//нет пересечения
    if (dot(Normal, C) < 0)  {
		return false;
	}
    vec3 edge3 = vertex1 - vertex3;
    vec3 diffP_v3 = P - vertex3;
    C = cross(edge3, diffP_v3);
	//нет пересечения
    if (dot(Normal, C) < 0)  {
		return false;
	}
    time = t;
    return true;
}

bool IntersectSquare(Ray ray, vec3 vertex1, vec3 vertex2, vec3 vertex3, vec3 vertex4, out float time ){
    time = -1;
    vec3 A = vertex2 - vertex1;
    vec3 B = vertex4 - vertex1;
	//ищем нормаль через векторное произведение
    vec3 Normal = cross(A, B);
    float N_and_Ray_DotProduct = dot(Normal, ray.direction);
	//нет пересечения
    if (abs(N_and_Ray_DotProduct) < EPSILON){
		return false;
	}
    float d = dot(Normal, vertex1);
    float t = -1. * (dot(Normal, ray.origin) - d) / N_and_Ray_DotProduct;
	//нет пересечения
    if (t < 0){ 
		return false;
	}
    vec3 P = ray.origin + t * ray.direction;

    vec3 edge1 = vertex2 - vertex1;
    vec3 diffP_v1 = P - vertex1;
    vec3 C = cross(edge1, diffP_v1);
	//нет пересечения
    if (dot(Normal, C) < 0)  {
		return false;
	}
    vec3 edge2 = vertex3 - vertex2;
    vec3 diffP_v2 = P - vertex2;
    C = cross(edge2, diffP_v2);
	//нет пересечения
    if (dot(Normal, C) < 0){
		return false;
	}
    vec3 edge3 = vertex4 - vertex3;
    vec3 diffP_v3 = P - vertex3;
    C = cross(edge3, diffP_v3);
	//нет пересечения
    if (dot(Normal, C) < 0){
		return false;
	}
    vec3 edge4 = vertex1 - vertex4;
    vec3 diffP_v4 = P - vertex4;
    C = cross(edge4, diffP_v4);
	//нет пересечения
    if (dot(Normal, C) < 0){
		return false;
	}
    time = t;
    return true;
}

// IN/OUT UNIFORM 
in vec3 interpolated_vertex;
out vec4 frag_color;

uniform Camera camera;
uniform vec2 scale;
uniform vec3 light_pos;

const int sphere_count=3;
const int triangle_count=4;
const int square_count=6;

uniform Triangle triangle[triangle_count];
uniform Square square[square_count];


layout(std430,binding=0)buffer SphereBuffer{
	Sphere sphere_data[];
};

//SCENE
//Sphere sphere={vec3(-1.0,-1.0,-2.0),2,vec3(1.0,1.0,2.0),0};
Material material={vec4(0.4,0.9,0.0,512.0)};

//ADDITIONAL LIGHT
uniform bool enable_additional_light;
vec3 light_pos_additional=vec3(10,10,10);
uniform float brightness_coeff;

Ray GenerateRay(Camera camera){
	vec2 coords=interpolated_vertex.xy*normalize(scale);
	vec3 direction=camera.view+camera.side*coords.x+camera.up*coords.y;
	return Ray(camera.position,normalize(direction));
}



bool Intersect(Ray ray,float start, float final, inout Intersection intersect){
	bool result=false;
	float time = start; 
	intersect.time =final;

	for(int i=0;i<sphere_count;i++){
		if(IntersectSphere(sphere_data[i],ray,time)&&(time<intersect.time)){
			intersect.time=time;
			intersect.point=ray.origin+ray.direction*time;
			intersect.normal=normalize(intersect.point-sphere_data[i].center);
			intersect.color=sphere_data[i].color;
			intersect.light_coeffs=material.light_coeffs;
			result=true;
		}
	}

	for (int i = 0; i < triangle_count; i++){
		if (IntersectTriangle(ray, triangle[i].v1, triangle[i].v2, triangle[i].v3, time) && time < intersect.time){
		intersect.point = ray.origin + ray.direction * time;
        intersect.normal = normalize(cross(triangle[i].v1 - triangle[i].v2, triangle[i].v3 - triangle[i].v2));
        intersect.color = triangle[i].color;
		intersect.light_coeffs = material.light_coeffs;
		intersect.time = time;
		result = true;
		}
	}

	for(int i = 0;i < square_count;i++){
        if(IntersectSquare(ray, square[i].v1, square[i].v2, square[i].v3, square[i].v4, time) && time < intersect.time){
                intersect.point = ray.origin + ray.direction * time;
                intersect.normal = normalize(cross(square[i].v1 - square[i].v2, square[i].v3 - square[i].v2));
                intersect.color = square[i].color;
                intersect.light_coeffs = material.light_coeffs;
                intersect.time = time;
                result = true;
        }
    }
	return result;
}


float Shadow(vec3 pos_light, Intersection intersect){
	//Point is lighted
	float shadowing=1.0;
	//Vector to the light source
	vec3 direction=normalize(pos_light-intersect.point);
	//Distance to the light source
	float distantLight=distance(pos_light,intersect.point);

	//Generation shadow ray for this source
	Ray shadowRay=Ray(intersect.point+direction*EPSILON,direction);


	//test intersection this ray with each scene object
	Intersection shadowIntersect;
	shadowIntersect.time=BIG;
	//trace ray from shadow ray being to the light source postion
	if(Intersect(shadowRay,0,distantLight,shadowIntersect)){
		//this light source is invisible in the intercesction point 
		shadowing=0.0;
	}
	return shadowing;
}

vec3 Phong(Intersection intersect,vec3 pos_light,float shadow){
	vec3 light=normalize(pos_light-intersect.point);
	float diffuse=max(dot(light,intersect.normal),0.0);
	vec3 view=normalize(camera.position-intersect.normal);
	vec3 reflected=reflect(-view,intersect.normal);
	float specular=pow(max(dot(reflected,light),0.0),intersect.light_coeffs.w);
	return intersect.light_coeffs.x*intersect.color+
		   intersect.light_coeffs.y*diffuse*intersect.color*shadow+
		   intersect.light_coeffs.z*specular;
}

vec4 Raytrace(Ray primary_ray){
	vec4 resultColor=vec4(0,0,0,0);
	Ray ray = primary_ray;

	Intersection intersect;
	intersect.time=BIG;
	float start=0;
	float final=BIG;

	if(Intersect(ray,start,final,intersect)){
		float shadowing=Shadow(light_pos,intersect);
		resultColor+=vec4(Phong(intersect,light_pos,shadowing),0);
	}
	if(enable_additional_light){
		if(Intersect(ray,start,final,intersect)){
			float shadowing=Shadow(light_pos_additional,intersect);
			resultColor+=vec4(Phong(intersect,light_pos_additional,shadowing),0);
		}
	}

	return brightness_coeff*resultColor;
}


void main(void){
	//trace
	Ray ray =GenerateRay(camera);
	frag_color=Raytrace(ray);

	//frag_color=vec4(abs(sphere_data[1].center),1);
}

