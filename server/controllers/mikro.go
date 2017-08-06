package controllers

import (
	"fmt"
	"time"

	"github.com/astaxie/beego"
	"github.com/edot92/smart_door/server/engine"
	"github.com/edot92/smart_door/server/models"
	"github.com/metakeule/fmtdate"
)

// DeviceController ...
type MikroController struct {
	beego.Controller
}

// Getlastvalue ...
// @router /getlastvalue [get]
func (c *MikroController) Getlastvalue() {

	type mikroResponStruct struct {
		StatusDoor1  string `json:"status_door1"`
		StatusDoor2  string `json:"status_door2"`
		ControlDoor1 string `json:"control_door1"`
		ControlDoor2 string `json:"control_door2"`
	}
	resModel, err := models.Getlastvalue()
	var resMikro mikroResponStruct
	resMikro.StatusDoor1 = resModel.StatusDoor1
	resMikro.StatusDoor2 = resModel.StatusDoor2
	resMikro.ControlDoor1 = resModel.ControlDoor1
	resMikro.ControlDoor2 = resModel.ControlDoor2
	if err != nil {
		resMikro.StatusDoor1 = "-1"
		resMikro.StatusDoor2 = "-1"
		resMikro.ControlDoor1 = "-1"
		resMikro.ControlDoor2 = "-1"
		c.Data["json"] = resMikro
	}
	c.Data["json"] = resMikro
	c.ServeJSON()
}

// Getlastvalue ...
// @router /updateclosealldoor [get]
func (c *MikroController) Updateclosealldoor() {

	var doorNumberStruct string
	c.Ctx.Input.Bind(&doorNumberStruct, "door") //id ==123
	fmt.Println("door")

	fmt.Println(doorNumberStruct)
	err := models.Updateclosealldoor(doorNumberStruct)
	if err != nil {
		c.Ctx.WriteString(err.Error())
		return
	}
	c.Ctx.WriteString("ok")
	return

	// c.Data["json"] =
	// c.ServeJSON()
}

// UpdatelogAlat ...
// @router /updatelogalat [get]
func (c *MikroController) UpdatelogAlat() {
	var lognya string
	c.Ctx.Input.Bind(&lognya, "log") //id ==123
	fmt.Println("log")
	fmt.Println(lognya)
	if lognya == "sistem_mendeteksi_kondisi_tidak_aman" {
		go func() {
			var listEmail []engine.DBEmail
			err := engine.KonDB.Find(&listEmail)
			if err != nil {
				date := fmtdate.Format("YYYY-MM-DD hh:mm:ss", time.Now())
				count := len(listEmail)
				for i := 0; i < count; i++ {
					fmt.Println("send email")
					go engine.KirimEmail(listEmail[i].Nama_lengkap, listEmail[i].Email, "SISTEM MIKROKONTROLLER "+lognya+" PUKUL "+date)
				}
			}
		}()
	}
	err := models.UpdatelogAlat(lognya)
	if err != nil {
		c.Ctx.WriteString(err.Error())
		return
	}
	c.Ctx.WriteString("ok")
	return
	// c.Data["json"] =
	// c.ServeJSON()
}
