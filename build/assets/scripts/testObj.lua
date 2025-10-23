function init(object)

end

count = 0
function update(object)
    object.transform.Rotate(object.transform, 2.0 * math.sin(count), Vector3(0.0, 1.0, 0.0))
    count = count + 0.01
end