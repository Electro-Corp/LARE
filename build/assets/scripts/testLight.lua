function init(light)
    light.transform.Translate(light.transform, Vector3(-0.5, -1.0, -0.3));
    light.transform.Scale(light.transform, Vector3(0.03, 0.031, 0.03));
    --light.ambient = Vector3(0.0001, 0.0001, 0.0001);
    --light.specular = Vector3(0.01, 0.01, 0.01);
    --light.diffuse = Vector3(0.001, 0.001, 0.001)1
end

count = 0.0
function update(light)
    --light.transform.Translate(light.transform, Vector3(1.5 * math.sin(count), 1.5 * math.cos(count), 1.5 * math.sin(count)))
    --count = count + 0.01
end

