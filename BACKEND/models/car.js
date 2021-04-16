const mongoose = require('mongoose');

const carSchema = new mongoose.Schema({
    number: {
        type: Number,
        required: true,
    },
    user:{
        type: mongoose.Schema.Types.ObjectId,
        ref: 'User'
    },
    model: {
        type: String,
        required: true,
    },
    status: {
        type: String
    },
    isOnCharging: {
        type: Boolean,
        default: false,
    },
    percentage: {
        type: Number
    },
    cells: {
        type: mongoose.Schema.Types.ObjectId,
        ref:'Cell'
    },
    dateOfInsertion: {
        type: Date,
        default: Date.now,
    }
});

//more front end friendly id

carSchema.virtual('id').get(function () {
    return this._id.toHexString();
});

carSchema.set('toJSON', {
    virtuals: true,
});

exports.Car = mongoose.model('Car', carSchema);
// exports.carSchema = carSchema;
