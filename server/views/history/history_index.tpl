<br>

<form action="" method="#" class="form-horizontal" role="form">

    <div class="form-group">
        <label class="control-label col-sm-2" for="pwd">Range Waktu:</label>
        <div class="col-sm-10">
            <input type="text" class="form-control" id="demo" placeholder="Pilih Waktu">
        </div>
    </div>
    <div class="form-group">
        <label class="control-label col-sm-2" for="pwd">Pilih Variabel:</label>
        <div class="col-sm-10">
            <!--<select class="form-control" id="dropdownRealtime">
    <option>Tegangan</option>
    <option>Arus</option>
    <option>Kelembapan</option>
  </select>-->
        </div>
    </div>

    <div class="form-group">
        <div class="col-sm-10 col-sm-offset-2">
            <button id="btncariHistory" class="btn btn-primary btn-block">Tampilkan Data</button>
        </div>
    </div>
</form>



<div class="row">
    <div class="table-responsive">

        <table class="table table-hover">
            <thead>
                <tr>
                    <th>No</th>
                    <th>Nilai</th>
                    <th>Waktu</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td></td>
                </tr>
            </tbody>
        </table>
    </div>
</div>


<!--range waktu -->

<script>
    $(document).ready(function () {

        $('#demo').daterangepicker({
            "timePicker": true,
            "timePicker24Hour": true,
            "timePickerSeconds": true,
            "startDate": "04/08/2017",
            "endDate": "04/14/2017"
        }, function (start, end, label) {
            console.log("New date range selected: ' + start.format('YYYY-MM-DD') + ' to ' + end.format('YYYY-MM-DD') + ' (predefined range: ' + label + ')");
        });
    });

</script>