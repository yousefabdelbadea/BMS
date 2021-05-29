const express = require('express');
const app = express();
const bodyParser = require('body-parser')
require('dotenv/config');
const api = process.env.API_URL;
const morgan = require('morgan');
const mongoose = require('mongoose');
const cors = require('cors');
require('dotenv/config');
const authJwt = require('./helpers/jwt');


//Routes
const usersRoutes = require('./routes/users');
const carsRoutes = require('./routes/cars');
const errorHandler = require("./helpers/error-handler");

//middleware
app.use(bodyParser.json()); //TP MAKE IT UNDERSTAND JASON SENT FROM FRONT END
app.use(morgan('tiny')); //console logging all requests, we can also save logs ing files
// app.use(authJwt()); //express-jwt
app.use(errorHandler);
app.use(cors()); //enable any backend to use our backend apis
app.options('*', cors()); //allowing all http request to passed from any origin


//routers
app.use(`${api}/users`, usersRoutes);
app.use(`${api}/cars`, carsRoutes);

app.get('/', ((req, res) => {
    res.send(200);
}))

//create database connection before starting server
mongoose.connect(process.env.CONNECTION_STRING, {
    useNewUrlParser: true,
    useUnifiedTopology: true,
    dbName:'eshop-db'
})
    .then(() => {
        console.log('data base connection is ready');
    })
    .catch(err => {
        console.log(err);
    })

app.listen(process.env.PORT || 3000 ,function(){

    console.log("listenning on port ");
});

