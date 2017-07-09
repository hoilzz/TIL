import React, { Component } from 'react';
import PropTypes from 'prop-types';
import {select_obj} from '../actions';
import {connect} from 'react-redux';
import ObjectiveEx from './ObjectiveEx';

const ObjectiveItem = ({updateSelection, objectiveInfo}) => {

    const objectiveToComponent = (objectiveInfo, updateSelection) => {
        return   (
            objectiveInfo.map((item, index) => {
                return (
                    <form key={item.answer_id}>
                        <p>{item.title}</p>
                        { 
                            exampleToComponent(
                                {
                                    options: item.options,
                                    answerId: item.answer_id
                                },
                                updateSelection
                            )
                        }
                    </form>
                );
            })
        )
    }   

    const exampleToComponent = (itemInfo, updateSelection) => {
        return(
            itemInfo.options.map( (option, index) => {            
                let isEtc = false;
                if(option.title === '기타') {
                    isEtc = true;
                }
                return (
                    <ObjectiveEx    
                        key = {option.id}
                        onUpdateSelection = {updateSelection}
                        option = {option}
                        answerId = {itemInfo.answerId}
                        isEtc = {isEtc}
                        />
                );
            })
        );
    }

    return(
        <div>
            {objectiveToComponent(objectiveInfo, updateSelection)}
        </div>
    );
}


ObjectiveItem.propTypes = {
    objectiveInfo: PropTypes.array,
    updateSelection: PropTypes.func
};

ObjectiveItem.defaultProps = {
    updateSelection: function(){console.warn('updateSelection not defined')},
    objectiveInfo: []
}

export default ObjectiveItem;