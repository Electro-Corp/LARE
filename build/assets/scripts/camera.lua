-- Basic camera 

zPos = 0
hPos = 0

speed = 0.01
sens = 0.1

lastX = 0
lastY = 0
firstPos = true

yaw = 0
pitch = 0

function init(camera) 
    camera.pAngle = 45
end


function update(camera)
    camera.position.z = zPos
    camera.position.x = hPos

    updateMouse(camera)
end

function onKeyPressed(camera, key)
    -- printing test
    if key == "w" then
        zPos = zPos + speed;
    end
    if key == "s" then
        zPos = zPos - speed;
    end
    if key == "a" then
        hPos = hPos + speed;
    end
    if key == "d" then
        hPos = hPos - speed;
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

    dir = Vector3(0,0,0);
    dir.x = math.cos(math.rad(yaw)) * math.cos(math.rad(pitch));
    dir.y = math.sin(math.rad(pitch));
    dir.z = math.sin(math.rad(yaw)) * math.cos(math.rad(pitch));

    camera.front = dir;

end