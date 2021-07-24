const mongoose = require('mongoose');

const cellDetailSchema = new mongoose.Schema({
    temperature:  {
        type: Number,
        required:true
    },
    current:  {
        type: Number,
        required:true
    },
    voltage:  {
        type: Number,
        required:true
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
