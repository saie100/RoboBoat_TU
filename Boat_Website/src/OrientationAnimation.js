
// Create a new scene that holds the animation
scene = new xeogl.Scene({
    canvas: "myCanvas"
});

// Load in the background for the boat (the skybox)
skybox = new xeogl.Skybox(scene,{
    src: "/assets/3D_Boat/xoGVD3X.jpg",
    size: 1000 // Default
});

// Load in the actual 3D model of the boat
BoatModel = new xeogl.STLModel(scene, {
  src: "/assets/3D_Boat/RoboBoat_3DAsset.stl",
  smoothNormals: true,
  position: [0, 0, 0],
  rotation: [-90, 0, 0]
});

// Configure the initial position of the camera relative to the BoatModel
camera = scene.camera;

camera.worldAxis = [
  1, 0, 0, // Right
  0, 1, 0, // Up
  0, 0, 1 // Forward
];

camera.look = [0.0000324249267578125,11.829302787780762,53.18818664550781];
camera.projection = "perspective";

// Gimbal lock camera yaw rotation to World +Z axis
camera.gimbalLock = true;

followAnimation = new xeogl.CameraFollowAnimation(scene,{
  target: BoatModel,
  fly: false,
  fit: false,
  fitFOV: 35
});

camera.eye = [0.06274989247322083, 25.782859802246094, 99.44140625];
