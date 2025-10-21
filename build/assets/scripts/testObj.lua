function init(object)

end

count = 0
function update(object)
    -- object.transform.Rotate(2.0f * sin(t), {0.0f, 1.0f, 0.0f})
    print(100.0 * sin(count))
    object.transform.Rotate(100.0 * sin(count), Vector3(0.0, 1.0, 0.0))
    count = count + 1
end