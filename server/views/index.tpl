<!DOCTYPE html>
<html lang="en">

<head>
  <title>Sukron Data Logger</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="static/vendor/bootstrap/bootstrap.min.css">
  <!--jquery 1.9.1-->
  <script src="static/vendor/jquery/jquery.min.js"></script>
  <script src="static/vendor/bootstrap/bootstrap.min.js"></script>
  <script src="static/vendor/moment/moment-with-locales.min.js"></script>
  <link rel="stylesheet" href="static/vendor/fontawesome/css/font-awesome.min.css">


  <!--<script src="http://code.jquery.com/ui/1.10.2/jquery-ui.js"></script>-->

  <script src="static/vendor/highcharts/highcharts.js"></script>
  <script src="static/vendor/highcharts/exporting.js"></script>
  <!-- Include Date Range Picker -->
  <script type="text/javascript" src="static/vendor/daterangepicker/daterangepicker.js"></script>
  <link rel="stylesheet" type="text/css" href="static/vendor/daterangepicker/daterangepicker.css" />
  <script type="text/javascript" src="static/js/jqx-all.js"></script>
  <link rel="stylesheet" type="text/css" href="static/css/jqx.base.css" />
  <link rel="stylesheet" type="text/css" href="static/css/jqx.bootstrap.css" />
</head>

<body>

  <div class="container-fluid">
    <ul class="nav nav-pills">
      <li class="active"><a data-toggle="pill" href="#home">Realtime</a></li>
      <li><a data-toggle="pill" href="#menu1">Tabel History</a></li>
    </ul>

    <div class="tab-content">
      <div id="home" class="tab-pane fade in active">

        <div class="form-group">
          <label for="sel1">Pilihan Grafik:</label>
          <select class="form-control" id="dropdownRealtime">
    <option>Tegangan</option>
    <option>Arus</option>
    <option>Kelembapan</option>
  </select>
        </div>
        <% template "realtimepage/realtime_index.tpl" .  %>
      </div>
      <div id="menu1" class="tab-pane fade">
        <% template "history/history_index.tpl" .  %>
      </div>
    </div>
  </div>

</body>

</html>