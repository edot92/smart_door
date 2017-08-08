package controllers

import (
	"encoding/json"

	"github.com/astaxie/beego"
	"github.com/edot92/smart_door/server/models"
)

// DeviceController ...
type DeviceController struct {
	beego.Controller
}

// Getlastvalue ...
// @router /getlastvalue [get]
func (c *DeviceController) Getlastvalue() {
	resModel, err := models.Getlastvalue()
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
	} else {
		c.Data["json"] = map[string]interface{}{"status": "success", "message": "berhasil mengambil nilai terakhir database", "data": resModel}

	}

	c.ServeJSON()
}

// Updatevalue ...
// @router /updatevalue [post]
func (c *DeviceController) Updatevalue() {
	// paramStruct ...
	type paramStruct struct {
		NumberDoor string `json:"number_door"`
	}
	var paramDoor paramStruct
	json.Unmarshal(c.Ctx.Input.RequestBody, &paramDoor)
	err := models.Updatevalue(paramDoor.NumberDoor)
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
	} else {
		c.Data["json"] = map[string]interface{}{"status": "success", "message": "berhasil mengupdate nilai terakhir database", "data": nil}
	}

	c.ServeJSON()
}
