package routers

import (
	"github.com/astaxie/beego"
	"github.com/astaxie/beego/context/param"
)

func init() {

	beego.GlobalControllerRouter["github.com/edot92/simple_datalogger_baterai/controllers:DeviceController"] = append(beego.GlobalControllerRouter["github.com/edot92/simple_datalogger_baterai/controllers:DeviceController"],
		beego.ControllerComments{
			Method: "Chart",
			Router: `/chart`,
			AllowHTTPMethods: []string{"post"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/simple_datalogger_baterai/controllers:DeviceController"] = append(beego.GlobalControllerRouter["github.com/edot92/simple_datalogger_baterai/controllers:DeviceController"],
		beego.ControllerComments{
			Method: "Realtimebox",
			Router: `/realtimebox`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/simple_datalogger_baterai/controllers:DeviceController"] = append(beego.GlobalControllerRouter["github.com/edot92/simple_datalogger_baterai/controllers:DeviceController"],
		beego.ControllerComments{
			Method: "Historylast",
			Router: `/historylast`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["github.com/edot92/simple_datalogger_baterai/controllers:DeviceController"] = append(beego.GlobalControllerRouter["github.com/edot92/simple_datalogger_baterai/controllers:DeviceController"],
		beego.ControllerComments{
			Method: "Historybydaterange",
			Router: `/historybydaterange`,
			AllowHTTPMethods: []string{"post"},
			MethodParams: param.Make(),
			Params: nil})

}
