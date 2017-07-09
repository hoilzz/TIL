// action을 이해하기 위해 천천히 가르쳐서 reducer 작성해보자.
import * as actions from '../actions/ActionTypes';
import Immutable, {Map, List, fromJS} from 'immutable';

export const initialState = fromJS({
    answerList: [
        {
            answer_id: 5,
            answerType: 'objective',
            title: '가장 좋아하는 음식은?',
            options: [
                {
                    id: 1,
                    title: '와퍼세트'
                },
                {
                    id: 2,
                    title: '네네치킨'
                },
                {
                    id: 3,
                    title: '타코'
                },
                {
                    id: 4,
                    title: '초밥'
                },
                {
                    id:5,
                    title: '기타'
                }
            ]
        },
        {
            answer_id: 6,
            answerType: 'objective',
            title: '가장 싫어하는 음식은?',
            options: [
                {
                    id: 12,
                    title: '미역국'
                },
                {
                    id: 13,
                    title: '모니터'
                },
                {
                    id: 14,
                    title: '키보드'
                },
                {
                    id: 15,
                    title: '마우스'
                },
                {
                    id: 16,
                    title: '기타'
                }
            ]
        }
    ],
    selection: []
});

/*
    객관식 문항의 보기 선택시 발생하는 리듀서
    @param action.selectionInfo = {
        answerId: Number,
        optionId: Number,
        etcValue: String
    }
*/

export const selectObjective = (state = initialState, action) => {
    
    /* 
        기존에 풀었던 객관식인지 확인
        - 풀었다면 : 해당 index 반환
        - 안풀었다면 : -1 반환
    */
    let checkExistAnswer = (selection, answerId) => {
        for(let i = 0; i<selection.size; i++){
            if(selection.get(i).toJS().answerId === answerId){
                return i;
            }
        }
        return -1;
    }

    switch (action.type){
        case actions.SELECT_EXAMPLE:
            let selection = state.get('selection');
            let answerIndex = checkExistAnswer(selection, action.selectionInfo.answerId);
            if(answerIndex === -1){
                return state.set('selection', 
                                selection.push(Map(action.selectionInfo))
                            );
            } else{
                console.log(action.selectionInfo);
                return state.set(
                        'selection', 
                        selection.set(answerIndex, Map(action.selectionInfo))
                       ) 
            }
        default:
            return state;
    }
}


