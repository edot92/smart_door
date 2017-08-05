<div class="row">
    <div id="container" style="min-width: 310px; height: 400px; margin: 0 auto"></div>
</div>
<div class="row">
    <div class="col-md-2">
        <div class="form-group">
            <label class="control-label col-sm-6" for="pwd">Temperature:</label>
            <div class="col-sm-6">
                <input type="text" class="form-control" id="" placeholder="???">
            </div>
        </div>
    </div>
    <div class="col-md-2">
        <div class="form-group">
            <label class="control-label col-sm-4" for="pwd">Humidity:</label>
            <div class="col-sm-6">
                <input type="text" class="form-control" id="" placeholder="???">
            </div>
        </div>
    </div>
    <div class="col-md-2">
        <div class="form-group">
            <label class="control-label col-sm-4" for="pwd">Tegangan:</label>
            <div class="col-sm-6">
                <input type="text" class="form-control" id="" placeholder="???">
            </div>
        </div>
    </div>
    <div class="col-md-2">
        <div class="form-group">
            <label class="control-label col-sm-4" for="pwd">Arus:</label>
            <div class="col-sm-6">
                <input type="text" class="form-control" id="" placeholder="???">
            </div>
        </div>
    </div>
    <div class="col-md-2">
        <div class="form-group">
            <label class="control-label col-sm-4" for="pwd">Daya:</label>
            <div class="col-sm-6">
                <input type="text" class="form-control" id="" placeholder="???">
            </div>
        </div>
    </div>
</div>
<script>
    $(document).ready(function () {
        Highcharts.setOptions({
            global: {
                useUTC: false
            }
        });

        Highcharts.chart('container', {
            chart: {
                type: 'spline',
                animation: Highcharts.svg, // don't animate in old IE
                marginRight: 10,
                events: {
                    load: function () {

                        // set up the updating of the chart each second
                        var series = this.series[0];
                        setInterval(function () {
                            var x = (new Date()).getTime(), // current time
                                y = Math.random();
                            series.addPoint([x, y], true, true);
                        }, 1000);
                    }
                }
            },
            title: {
                text: 'Tegangan Baterai'
            },
            xAxis: {
                type: 'datetime',
                tickPixelInterval: 150
            },
            yAxis: {
                title: {
                    text: 'Volt DC'
                },
                plotLines: [{
                    value: 0,
                    width: 1,
                    color: '#808080'
                }]
            },
            tooltip: {
                formatter: function () {
                    return '<b>' + this.series.name + '</b><br/>' +
                        Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) + '<br/>' +
                        Highcharts.numberFormat(this.y, 2);
                }
            },
            legend: {
                enabled: false
            },
            exporting: {
                enabled: false
            },
            series: [{
                name: 'Random data',
                data: (function () {
                    // generate an array of random data
                    var data = [],
                        time = (new Date()).getTime(),
                        i;

                    for (i = -19; i <= 0; i += 1) {
                        data.push({
                            x: time + i * 1000,
                            y: Math.random()
                        });
                    }
                    return data;
                }())
            }]
        });
    });

</script>