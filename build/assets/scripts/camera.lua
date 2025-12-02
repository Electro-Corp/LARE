-- Basic camera 

zPos = 0
hPos = 0

speed = 1
sens = 0.1
dTime = 0
lastF = 0

lastX = 0
lastY = 0
firstPos = true

yaw = 0
pitch = 0

cam = 0

function init(camera) 
    camera.pAngle = 45
    cam = camera
end


function update(camera)
    curFrame = LARE:getCurrentFrame()
    dTime = curFrame - lastF
    lastF = curFrame

    updateMouse(camera)
end

function onKeyPressed(camera, key)
    sSpeed = speed * dTime
    -- printing test
    if key == "w" then
        cam.offsetFB(cam, sSpeed)
    end
    if key == "s" then
        cam.offsetFB(cam, -1 * sSpeed)
    end
    if key == "a" then
        cam.offsetLR(cam, -1 * sSpeed)
    end
    if key == "d" then
        cam.offsetLR(cam, sSpeed)
    end
end

function updateMouse(camera)
    mouseX = LARE.mousePosition.x
    mouseY = LARE.mousePosition.y

    if firstPos == true then
        lastX = mouseX
        lastY = mouseY 
        firstPos = false
    end

    xOff = mouseX - lastX
    yOff = lastY - mouseY

    lastX = mouseX
    lastY = mouseY

    xOff = xOff * sens
    yOff = yOff * sens

    yaw = yaw + xOff
    pitch = pitch + yOff

    if pitch > 89.0 then
        pitch = 89.0
    end
    if pitch < -89.0 then
        pitch = -89.0
    end

    dir = Vector3(0,0,0)
    dir.x = math.cos(math.rad(yaw)) * math.cos(math.rad(pitch))
    dir.y = math.sin(math.rad(pitch))
    dir.z = math.sin(math.rad(yaw)) * math.cos(math.rad(pitch))

    camera.front = dir;
end

-- Make these into a seperate file later
function constantMul(c, v2)
    return Vector3(c * v2.x, c * v2.y, c * v2.z)
end

function addV(v1, v2)
    return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z)
end