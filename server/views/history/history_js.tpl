<script>
    var baseUrl = "http://localhost:8080";
    $(document).ready(function () {
        function reloadTableHistory(data) {
            var source =
                {
                    localdata: data,
                    datatype: "json",
                    datafields:
                    [
                        { name: 'Temperature', type: 'number' },
                        { name: 'Humidity', type: 'number' },
                        { name: 'Current', type: 'number' },
                        { name: 'Shuntvoltage', type: 'number' },
                        { name: 'Busvoltage', type: 'number' },
                        { name: 'Loadvoltage', type: 'number' },
                        { name: 'UpdateAt', type: 'date' },
                        { name: 'CreatedAt', type: 'date' }
                    ],
                    id: 'ID'
                };
            var dataAdapter = new $.jqx.dataAdapter(source)
            //initialize jqxGrid
            $("#grid").jqxGrid(
                {
                    source: dataAdapter,
                    showstatusbar: true,
                    editable: false,
                    columns:
                    [
                        { text: 'Temperature', datafield: 'Temperature', width: 100 },
                        { text: 'Humidity', datafield: 'Humidity', width: 100 },
                        { text: 'Current', datafield: 'Current', width: 100 },
                        { text: 'Shuntvoltage', datafield: 'Shuntvoltage', width: 100 },
                        { text: 'Busvoltage', datafield: 'Busvoltage', width: 100 },
                        { text: 'Loadvoltage', datafield: 'Loadvoltage', width: 100 },
                        { text: 'UpdateAt', datafield: 'UpdateAt', width: 100 },
                        { text: 'CreatedAt', datafield: 'CreatedAt', width: 100 },
                    ]
                });
        }

        $('#btncariHistory').on('click', function (event) {
            event.preventDefault();
            var dataJson;
            axios.get(baseUrl, { Data: dataJson })
                .then(res => {
                    console.log(res)
                }).catch(err => {
                    alert(err)
                })
        })
    }//end doc

</script>