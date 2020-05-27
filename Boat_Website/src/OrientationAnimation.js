 scene = new xeogl.Scene({
    canvas: "myCanvas"
});

 skybox = new xeogl.Skybox(scene,{
    src: "/assets/3D_Boat/xoGVD3X.jpg",
    size: 1000 // Default
});

 BoatModel = new xeogl.STLModel(scene, {
  src: "/assets/3D_Boat/RoboBoat_3DAsset.stl",
  smoothNormals: true,
  position: [0, 0, 0],
  rotation: [-90, 0, 0]
});

var cameraControl = new xeogl.CameraControl(scene);

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

cameraControl.active = false;

/*
var scene = new xeogl.Scene({
  canvas: "myCanvas"
});

var skybox = new xeogl.Skybox(scene, {
  src: "../assets/3D_Boat/xoGVD3X.jpg",
  size: 100 // Default
});

var BoatModel = new xeogl.STLModel(scene, {
  src: "../assets/3D_Boat/RoboBoat_3DAsset.stl",
  smoothNormals: true,
  position: [0, 0, 0],
  rotation: [-90, 0, 0]
});



var camera = scene.camera;

camera.worldAxis = [
  1, 0, 0, // Right
  0, 0, 1, // Up
  0, 1, 0 // Forward
];

// Position camera with "up" pointing along World +Z axis

camera.projection = "perspective";

// Gimbal lock camera yaw rotation to World +Z axis

camera.gimbalLock = true;
camera.eye = [ 0.004382897634059191,61.35212707519531,43.9945182800293];
camera.look = [0.0000324249267578125,11.829302787780762,53.18818664550781];
camera.up = [0, 0, 1];


var followAnimation = new xeogl.CameraFollowAnimation( {
  target: BoatModel,
  fly: true.
  fit: false,
  fitFOV: 35
});



new xeogl.CameraControl(scene);
*/
