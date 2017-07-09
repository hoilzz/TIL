import {connect} from 'react-redux';
import * as actions from '../actions';
import ObjectiveItem from '../components/ObjectiveItem';


const mapDispatchToProps = (dispatch) => ({
    updateSelection: ({optionId, answerId, etcValue = ''}) => {
        dispatch(actions.selectExample({optionId, answerId, etcValue}));
    }
})

const mapStateToProps = (state) => ({
        objectiveInfo: state.get('answerList').toJS() 
})

const ObjectiveContainer = connect(mapStateToProps, mapDispatchToProps)(ObjectiveItem);

export default ObjectiveContainer;