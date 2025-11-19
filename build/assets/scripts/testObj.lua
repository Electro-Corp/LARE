function init(object)
    object.transform.Scale(object.transform, Vector3(0.1, 0.1, 0.1))
    object.transform.Rotate(object.transform, 45, Vector3(0.5, 0.0, 1.0))
    object.transform.Translate(object.transform, Vector3(-1.0, -2.0, -5.0))
end

count = 0
function update(object)
    object.transform.Rotate(object.transform, 2.0 * math.sin(count), Vector3(0.0, 1.0, 0.0))
    count = count + 0.01
end

function onKeyPressed(object, key)
    -- printing test
    if key == "h" then
        print("h pressed")
    end
end