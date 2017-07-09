
import * as types from './ActionTypes';

/*
    @param {
        action_id: Number,
        option_id: Number,
        etcValue : String
    }
*/
export function selectExample(selectionInfo){
    return {
        type: types.SELECT_EXAMPLE,
        selectionInfo
    }
}

// export function make_response(response){
//     return {
//         type: types.MAKE_RESPONSE_FORM,
//         response
//     }
// }