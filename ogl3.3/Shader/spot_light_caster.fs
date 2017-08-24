#version 330 core
out vec4 FragColor;

uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;


struct Material{
    float shininess;
};

uniform Material material;
uniform sampler2D diffuse;
uniform sampler2D specular;
uniform sampler2D emission;

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform Light light;

void main(){
    
    // check if lighting in the spotlight cone
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction));


    if (theta > light.cutOff)
    {
         // 环境光
        vec3 ambient = light.ambient * vec3(texture(diffuse, TexCoord));

        // 漫反射 
        vec3 norm = normalize(Normal);

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * vec3(texture(diffuse, TexCoord));

        // 镜面光
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec *  vec3(texture(specular, TexCoord));  

        // attenuation
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

        ambient  *= attenuation;  
        diffuse   *= attenuation;
        specular *= attenuation;   
        
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    }else
    {
        // else, use ambient light so scene isn't completely dark outside the spotlight.
        FragColor = vec4(light.ambient * texture(diffuse, TexCoord).rgb, 1.0);

    }
}