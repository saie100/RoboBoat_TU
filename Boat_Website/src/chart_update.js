

function updateGamepadChart(idx, val){

  Chart_Controller.data.datasets[idx].data[0].y = val;
  Chart_Controller.update(0);

}
