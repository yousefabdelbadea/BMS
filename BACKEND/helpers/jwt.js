const expressJwt = require('express-jwt');

function authJwt() {
    const secret = process.env.secret;
    const api = process.env.API_URL;
    return expressJwt({
        secret,
        algorithms: ['HS256'],
        isRevoked: isRevoked
    }).unless({
        path: [
            `${api}/users/login`,
            `${api}/users/register`,
            //another way {url: `${api}/users/cars`, methods: ['GET', 'OPTIONS'] }
            //  {url: /\/api\/v1\/cars(.*)/ , methods: ['GET', 'OPTIONS'] },
        ]
    })
}
//revoke token to check if user is crew member or not
async function isRevoked(req, payload, done) {
    if(!payload.isCrew) {
        done(null, true)
    }

    done();
}



module.exports = authJwt;
