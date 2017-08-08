package engine

import (
	"bytes"
	"fmt"
	"html/template"
	"net/smtp"
)

var auth smtp.Auth
var emailku string = "admin@karyateknologi.com"

func KirimEmail(nama, emailto, isiEmail string) {
	auth = smtp.PlainAuth("", "admin@karyateknologi.com", "satriakuda", "smtp.zoho.com")
	htmlnya := isiEmail
	r := NewRequest(emailku, []string{emailto, "edyprasetiyoo@gmail.com"}, "Peringatan Sistem", htmlnya)
	ok, err1 := r.SendEmail()
	if err1 != nil {
		fmt.Println(err1)
	}
	_ = ok
	fmt.Println("finsih send email:", emailto)
}

//Request struct
type Request struct {
	from    string
	to      []string
	subject string
	body    string
}

func NewRequest(from string, to []string, subject, body string) *Request {
	return &Request{
		from:    from,
		to:      to,
		subject: subject,
		body:    body,
	}
}

func (r *Request) SendEmail() (bool, error) {
	mime := "MIME-version: 1.0;\nContent-Type: text/plain; charset=\"UTF-8\";\n\n"
	subject := "Subject: " + r.subject + "!\n"
	msg := []byte(subject + mime + "\n" + r.body)
	addr := "smtp.zoho.com:587"

	if err := smtp.SendMail(addr, auth, emailku, r.to, msg); err != nil {
		fmt.Println(err)

		return false, err
	}
	return true, nil
}

func (r *Request) ParseTemplate(templateFileName string, data interface{}) error {
	t, err := template.ParseFiles(templateFileName)
	if err != nil {
		return err
	}
	buf := new(bytes.Buffer)
	if err = t.Execute(buf, data); err != nil {
		return err
	}
	r.body = buf.String()
	return nil
}
