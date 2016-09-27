## Understanding Polymorphic associations in Rails

#### Introduction
With polymorphic associations, model은 1개 이상의 다른 모델에 belongs_to 할 수 있다.

#### Basics

비슷해 보이는 model association을 가질 때 ,
예를 들어 Course와 Lab model을 가진다고 가정해보자.
Course와 Lab 각각은 Teaching Assistants를 필요한다.
그래서 Course and Labs와 상응하는 TA를 associate 한다.

만약 has_many/belongs_to를 사용한다면,
course의 TA와 Lab의 TA 2개의 비슷한 모델을 가질 거다.

2개 모델 대신에 polymorphic association을 통해  1개의 모델을 가질 수 있다.


> rails g model TeachingAssistant name:string ta_duty_id: integer ta_duty_type:string

ta_duty_id 는 외래키
ta_duty_type은 TeachingAssistant 모델에게 associated된 모델을 말한다.


  class CreateTeachingAssistants < ActiveRecord::Migration
    def change
      create_table :teaching_assistants do |t|
        t.string :name
        t.integer :ta_duty_id
        t.string :ta_duty_type

        t.timestamps
      end
    end
  end


모델은 생성됐다. polymorphic association model TeachingAssistant를 세팅해보자.

class TeachingAssistant < ActiveRecord::Base
  belongs_to :ta_duty, polymorphic: true
end

다른 모델 대신에 Teaching Assistant belong_to ta_duty 를 선언하여 우리는 polymorphic association을 만들 수 있다.

우리는 어떤 ta_duty model/class를 가지지 않는 다는 것을 주목해

ta_duty 는 polymorphic association을 care한다.


다른 관점에서 보자.

/app/models/course.rb

class SectionA < ActiveRecord::Base
  has_many :teaching_assistants, as: :ta_duty
end

/app/models/lab.rb

class Lab < ActiveRecord::Base
  has_many :teaching_assistants, as: :ta_duty
end
