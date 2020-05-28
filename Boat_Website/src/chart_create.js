var ctx = document.getElementById('Chart_OrientationDeg').getContext('2d');
var Chart_OrientationDeg = new Chart(ctx, {
  // The type of chart we want to create
  type: 'line',

  // The data for our dataset
  data: {
    labels: [],
    datasets: [{
      label: 'X',
      borderColor: 'rgb(255, 0, 0)',
      data: []
    }, {
      label: 'Y',
      borderColor: 'rgb(0, 255, 0)',
      data: []
    }, {
      label: 'Z',
      borderColor: 'rgb(0, 0, 255)',
      data: []
    }]
  },

  // Configuration options go here
  // Look at this link for time configuration
  // https://www.chartjs.org/docs/latest/axes/cartesian/time.html#display-formats
  options: {
    plugins: {
      datalabels: {
        display: false
      }
    },
    responsive: true,
    maintainAspectRatio: true,
    scales: {
      xAxes: [{
        scaleLabel: {
          display: true,
          labelString: 'Measured Time'
        },
      }],
      yAxes: [{
        scaleLabel: {
          display: true,
          labelString: 'Orientation [deg]'
        },
      }]
    }
  }
});

var ctx = document.getElementById('Chart_Acceleration').getContext('2d');
var Chart_Acceleration = new Chart(ctx, {
  // The type of chart we want to create
  type: 'line',
  // The data for our dataset
  data: {
    labels: [],
    datasets: [{
      label: 'X',
      borderColor: 'rgb(255, 0, 0)',
      data: []
    }, {
      label: 'Y',
      borderColor: 'rgb(0, 255, 0)',
      data: []
    }, {
      label: 'Z',
      borderColor: 'rgb(0, 0, 255)',
      data: []
    }]
  },
  // Configuration options go here
  options: {
    plugins: {
      datalabels: {
        display: false
      }
    },
    responsive: true,
    maintainAspectRatio: true,
    scales: {
      xAxes: [{
        scaleLabel: {
          display: true,
          labelString: 'Measured Time'
        },
      }],
      yAxes: [{
        scaleLabel: {
          display: true,
          labelString: 'Acceleration [m/(s^2)]'
        },
      }]
    }
  }
});

var ctx = document.getElementById('Chart_AngVel').getContext('2d');
var Chart_AngularVelocity = new Chart(ctx, {
  // The type of chart we want to create
  type: 'line',
  // The data for our dataset
  data: {
    labels: [],
    datasets: [{
      label: 'X',
      borderColor: 'rgb(255, 0, 0)',
      data: []
    }, {
      label: 'Y',
      borderColor: 'rgb(0, 255, 0)',
      data: []
    }, {
      label: 'Z',
      borderColor: 'rgb(0, 0, 255)',
      data: []
    }]
  },
  // Configuration options go here
  options: {
    plugins: {
      datalabels: {
        display: false
      }
    },
    responsive: true,
    maintainAspectRatio: true,
    scales: {
      xAxes: [{
        scaleLabel: {
          display: true,
          labelString: 'Measured Time'
        },
      }],
      yAxes: [{
        scaleLabel: {
          display: true,
          labelString: 'Angular Velocity [rad/s]'
        },
      }]
    }
  }
});

var ctx = document.getElementById('Chart_Magnetometer').getContext('2d');
var Chart_Magnetometer = new Chart(ctx, {
  // The type of chart we want to create
  type: 'line',
  // The data for our dataset
  data: {
    labels: [],
    datasets: [{
      label: 'X',
      borderColor: 'rgb(255, 0, 0)',
      data: []
    }, {
      label: 'Y',
      borderColor: 'rgb(0, 255, 0)',
      data: []
    }, {
      label: 'Z',
      borderColor: 'rgb(0, 0, 255)',
      data: []
    }]
  },
  // Configuration options go here
  options: {
    plugins: {
      datalabels: {
        display: false
      }
    },
    responsive: true,
    maintainAspectRatio: true,
    scales: {
      xAxes: [{
        scaleLabel: {
          display: true,
          labelString: 'Measured Time'
        },
      }],
      yAxes: [{
        scaleLabel: {
          display: true,
          labelString: 'Magnetic Flux [uT]'
        },
      }]
    }
  }
});

var ctx = document.getElementById('Chart_Battery').getContext('2d');
var Chart_Battery = new Chart(ctx, {
  // The type of chart we want to create
  type: 'horizontalBar',
  // The data for our dataset
  data: {
    labels: ['6-Cell', '4-Cell', '3-Cell (A)', '3-Cell (B)'],
    datasets: [{
      backgroundColor: '#003f5c',
      label: 'Cell 1',
      data: []
    }, {
      backgroundColor: '#444e86',
      label: 'Cell 2',
      data: []
    }, {
      backgroundColor: '#955196',
      label: 'Cell 3',
      data: []
    }, {
      backgroundColor: '#dd5182',
      label: 'Cell 4',
      data: []
    }, {
      backgroundColor: '#ff6e54',
      label: 'Cell 5',
      data: []
    }, {
      backgroundColor: '#ffa600',
      label: 'Cell 6',
      data: []
    }]
  },
  // Configuration options go here
  options: {
    tooltips: {
      mode: 'index',
      intersect: true
    },
    plugins: {
      datalabels: {
        color: 'white',
        display: function(context) {
          return context.dataset.data[context.dataIndex] > 0;
        },
        font: {
          weight: 'bold'
        }
      }
    },
    responsive: true,
    maintainAspectRatio: true,
    scales: {
      xAxes: [{
        ticks: {
          min: 0,
          max: 26,
          stepSize: 1
        },
        scaleLabel: {
          display: true,
          labelString: 'Voltage [V]'
        },
        stacked: true
      }],
      yAxes: [{
        ticks: {
          beginAtZero: true
        },
        stacked: true
      }]
    }
  }
});

var ctx = document.getElementById('Chart_Controller').getContext('2d');
var Chart_Controller = new Chart(ctx, {
  // The type of chart we want to create
  type: 'bubble',
  // The data for our dataset

  data: {
    datasets: [{
      backgroundColor: 'rgb(255, 0, 0)',
      label: 'Left Joystick',
      //backgroundColor: 'rgb(255, 99, 132)',
      data: [{
        x: -1,
        y: 0,
        r: 20
      }]
    }, {
      backgroundColor: 'rgb(0, 255, 0)',
      label: 'Right Joystick',
      //backgroundColor: 'rgb(255, 99, 132)',
      data: [{
        x: 1,
        y: 0,
        r: 20
      }]
    }]
  },
  // Configuration options go here
  options: {
    plugins: {
      datalabels: {
        display: false
      }
    },
    tooltips: {
      enabled: false
    },
    responsive: true,
    maintainAspectRatio: true,
    scales: {
      xAxes: [{
        display: false,
        ticks: {
          min: -2,
          max: 2
        },
      }],
      yAxes: [{
        ticks: {
          min: -1.5,
          max: 1.5
        },
      }]
    }
  }
});

var ctx = document.getElementById('Chart_LIDAR').getContext('2d');
var Chart_LIDAR = new Chart(ctx, {
  type: 'scatter',
  data: {
    datasets: [{
      label: 'Scatter Dataset',
      backgroundColor: 'rgb(255, 0, 0)',
      data: [{
        x: 0,
        y: 0
      }]
    }]
  },
  options: {
    responsive: true,
    maintainAspectRatio: true,
    scales: {
      xAxes: [{
        ticks: {
          min: -6,
          max: 6
        },
        scaleLabel: {
          display: true,
          labelString: 'Distance [m]'
        }
      }],
      yAxes: [{
        ticks: {
          min: 0,
          max: 4
        },
        scaleLabel: {
          display: true,
          labelString: 'Distance [m]'
        }
      }]
    },
    legend: {
      display: false,
    },
    plugins: {
      datalabels: {
        display: false
      },
      zoom: {
        pan: {
          enabled: true,
          mode: "xy",
          speed: 10,
          threshold: 10,
          rangeMin: {
            // Format of min zoom range depends on scale type
            x: -25,
            y: 0
          },
          rangeMax: {
            // Format of max zoom range depends on scale type
            x: 25,
            y: 25
          }
        },
        zoom: {
          enabled: true,
          drag: false,
          mode: 'xy',
          rangeMin: {
            // Format of min zoom range depends on scale type
            x: -25,
            y: 0
          },
          rangeMax: {
            // Format of max zoom range depends on scale type
            x: 25,
            y: 25
          }
        }
      }
    }
  }
});
