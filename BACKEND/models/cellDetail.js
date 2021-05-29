const mongoose = require('mongoose');

const cellDetailSchema = new mongoose.Schema({
    temperature:  {
        type: Number
    },
    current:  {
        type: Number
    },
    voltage:  {
        type: Number
    },
    percentage: {
        type: Number
    },
    dateOfRecord: {
        type: Date,
        default: Date.now
    }
});

cellDetailSchema.virtual('id').get(function () {
    return this._id.toHexString();
});

cellDetailSchema.set('toJSON', {
    virtuals: true,
});

exports.CellDetail = mongoose.model('CellDetail', cellDetailSchema);
// exports.cellSchema = cellSchema;
