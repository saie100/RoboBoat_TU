
// Byron Gaspard's MapBox API token
mapboxgl.accessToken = 'pk.eyJ1IjoiYnlyb25nYXNwYXJkIiwiYSI6ImNrOGtudGIxMzAzdm8zZ28yNDFuMHcwdXQifQ.fY_gpP0xJ77xE-OyyH_wbg';
// Create a new map centered at Temple University Engineering school to start
map = new mapboxgl.Map({
  container: 'map',
  style: 'mapbox://styles/mapbox/outdoors-v11',
  center: [-75.152842, 39.982492], // Set to Temple Engineering location on startup
  zoom: 16
});
// Add a red marker to temple engineering school to start
marker = new mapboxgl.Marker({
  color: `rgb(255, 0, 0)`
}).setLngLat([-75.152842, 39.982492]).addTo(map);
