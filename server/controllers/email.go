package controllers

import (
	"encoding/json"

	"github.com/astaxie/beego"
	"github.com/edot92/smart_door/server/models"
)

// DeviceController ...
type EmailController struct {
	beego.Controller
}

// Getallemail  ...
// @router /getallemail [get]
func (c *EmailController) Getallemail() {
	res, err := models.Getallemail()
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
	} else {
		c.Data["json"] = map[string]interface{}{"status": "success", "message": "berhasil mengambil data email", "data": res}
	}
	c.ServeJSON()
}

// Deleteemailbyid ...
// @router /deleteemailbyid [post]
func (c *EmailController) Deleteemailbyid() {
	type paramStruct struct {
		ID int `json:"id"`
	}
	var paramDoor paramStruct
	err := json.Unmarshal(c.Ctx.Input.RequestBody, &paramDoor)
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
		c.ServeJSON()
		return
	}
	err = models.Deleteemailbyid(paramDoor.ID)
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
	} else {
		c.Data["json"] = map[string]interface{}{"status": "success", "message": "berhasil menhapus email", "data": nil}
	}
	c.ServeJSON()
}

// Addnewemail ...
// @router /addnewemail [post]
func (c *EmailController) Addnewemail() {
	type paramStruct struct {
		Nama  string `json:"nama_lengkap"`
		Email string `json:"email"`
	}
	var paramDoor paramStruct
	err := json.Unmarshal(c.Ctx.Input.RequestBody, &paramDoor)
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
		c.ServeJSON()
		return
	}
	err = models.Addnewemail(paramDoor.Nama, paramDoor.Email)
	if err != nil {
		c.Data["json"] = map[string]interface{}{"status": "failed", "message": err.Error(), "data": nil}
	} else {
		c.Data["json"] = map[string]interface{}{"status": "success", "message": "berhasil menambahkan email", "data": nil}
	}
	c.ServeJSON()
}
