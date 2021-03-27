const mongoose = require('mongoose');

const cellSchema = new mongoose.Schema({
    number: {
        type: Number,
        required: true,
    },
    model: {
        type: String,
        required: true,
    },
    temperature:  {
        type: Number
    },
    current:  {
        type: Number
    },
    voltage:  {
        type: Number
    },
    status: {
        type: String
    },
    percentage: {
        type: Number
    }
});

cellSchema.virtual('id').get(function () {
    return this._id.toHexString();
});

cellSchema.set('toJSON', {
    virtuals: true,
});

exports.Cell = mongoose.model('Cell', cellSchema);
// exports.cellSchema = cellSchema;
